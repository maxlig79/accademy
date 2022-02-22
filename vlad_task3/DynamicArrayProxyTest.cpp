#define BOOST_TEST_MODULE DynamicArrayProxy_test

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <Common.hpp>
#include <ServerProxyObject.hpp>
#include <ClientProxyObject.hpp>
#include <unistd.h>
#include <thread>
#include <sys/stat.h>
#include <signal.h>
#include <fstream>
#include <boost/format.hpp>
#include <cstring>
#include <algorithm>
#include <numeric>
#include <execution>
#include <mutex>

using namespace common;

struct Fixture
{
    const char *const client_input_pipes[3] = {"/tmp/cat_client_input_0", "/tmp/cat_client_input_1"};
    Fixture()
    {
        remove(client_input_pipes[0]);
        remove(client_input_pipes[1]);
        mkfifo(client_input_pipes[0], S_IWUSR | S_IRUSR | S_IROTH);
        mkfifo(client_input_pipes[1], S_IWUSR | S_IRUSR | S_IROTH);
    }
    ~Fixture()
    {
        remove(client_input_pipes[0]);
        remove(client_input_pipes[1]);
    }
    int count = 100;
    char *trim(char *s)
    {
        char *back = s + strlen(s);
        while (isspace(*--back))
            ;
        *(back + 1) = '\0';
        return s;
    }
};

BOOST_FIXTURE_TEST_CASE(DynamicArrayProxy_single_client, Fixture)
{
    std::unique_ptr<FILE, decltype(&pclose)> serv(popen("./main_server", "r"), pclose);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::string cmd = (boost::format("./main_client --no-prompt < %s") % client_input_pipes[0]).str();
    std::unique_ptr<FILE, decltype(&pclose)> client(popen(cmd.c_str(), "r"), pclose);
    std::ofstream input_pipe(client_input_pipes[0]);
    input_pipe << "add\nstr1\nget\n0\ndelete\nstr1\nexit" << std::endl;
    char line[100] = {0};

    fgets(line, 100, client.get());
    BOOST_CHECK(!strcmp(line, "String added successfully\n"));
    memset(line, 0, sizeof(line));
    fgets(line, 100, client.get());
    BOOST_CHECK(!strcmp(line, "arr[0]=\"str1\"\n"));
    memset(line, 0, sizeof(line));
    fgets(line, 100, client.get());
    BOOST_CHECK(!strcmp(line, "String deleted successfully\n"));
}

BOOST_FIXTURE_TEST_CASE(DynamicArrayProxy_multiple_clients, Fixture)
{
    std::unique_ptr<FILE, decltype(&pclose)> serv(popen("./main_server", "r"), pclose);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::string cmd1 = (boost::format("./main_client --no-prompt < %s") % client_input_pipes[0]).str();
    std::string cmd2 = (boost::format("./main_client --no-prompt < %s") % client_input_pipes[1]).str();
    std::unique_ptr<FILE, decltype(&pclose)> client1(popen(cmd1.c_str(), "r"), pclose);
    std::unique_ptr<FILE, decltype(&pclose)> client2(popen(cmd2.c_str(), "r"), pclose);

    std::ofstream input1(client_input_pipes[0]);
    std::ofstream input2(client_input_pipes[1]);

    std::vector<int> vec(100);
    std::iota(vec.begin(), vec.end(), 0);
    std::mutex m1, m2;
    std::for_each(std::execution::par, vec.begin(), vec.end(),
                  [&](const int i)
                  {
                      std::string str1 = (boost::format("add\nstr1_%d\n") % i).str();
                      m1.lock();
                      input1 << str1 << std::endl;
                      m1.unlock();
                      std::string str2 = (boost::format("add\nstr2_%d\n") % i).str();
                      m2.lock();
                      input2 << str2 << std::endl;
                      m2.unlock();
                  });

    // std::cout << "Add completed" << std::endl;
    std::for_each(std::execution::par, vec.begin(), vec.end(),
                  [&](const int i)
                  {
                      std::string input = (boost::format("get\n%d") % i).str();
                      m1.lock();
                      input1 << input << std::endl;
                      m1.unlock();
                      m2.lock();
                      input2 << input << std::endl;
                      m2.unlock();
                  });
    // std::cout << "Get completed" << std::endl;
    char line[100] = {0};
    for (int i = 0; i < 100; i++)
    {
        const char msg[] = "String added successfully";
        fgets(line, sizeof(line), client1.get());
        // std::cout << line;
        BOOST_CHECK(!strcmp(msg, trim(line)));
        memset(line, 0, sizeof(line));
        fgets(line, sizeof(line), client2.get());
        // std::cout << line;
        // std::cout << i << std::endl;
        BOOST_CHECK(!strcmp(msg, trim(line)));
        memset(line, 0, sizeof(line));
    }
    // std::cout << "Check adds completed" << std::endl;
    int res[2][100] = {0};
    for (int i = 0; i < 100; i++)
    {
        std::string fmt;

        // msg = (boost::format("arr[%d]=\"str1%d\"") % i % i).str();
        fmt = "arr[%*d]=\"str%d_%d\"";
        int idx, client, val;

        fgets(line, sizeof(line), client1.get());
        // std::cout << line;
        trim(line);
        sscanf(line, fmt.c_str(), &client, &val);
        res[client - 1][val] = 1;
        memset(line, 0, sizeof(line));

        fgets(line, sizeof(line), client2.get());
        // std::cout << line;
        trim(line);
        sscanf(line, fmt.c_str(), &client, &val);
        res[client - 1][val] = 1;
        memset(line, 0, sizeof(line));
    }
    BOOST_CHECK(std::all_of(res[0], res[0] + 100, [&](const int i)
                            { return i == 1; }));
    BOOST_CHECK(std::all_of(res[1], res[1] + 100, [&](const int i)
                            { return i == 1; }));
    input1 << "exit" << std::endl;
    input2 << "exit" << std::endl;
    char s[100];
    while (fgets(s, 100, serv.get()) != NULL)
    {
        std::cout << s;
        memset(s, 0, 100);
    }
}