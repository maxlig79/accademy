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

    for (int i = 0; i < 100; i++)
    {
        std::string str1 = (boost::format("add\nstr1%d\n") % i).str();
        input1 << str1 << std::endl;
        std::string str2 = (boost::format("add\nstr2%d\n") % i).str();
        input2 << str2 << std::endl;
    }
    for (int i = 0; i < 100; i++)
    {
        std::string input = (boost::format("get\n%d") % i).str();
        input1 << input << std::endl;
        input2 << input << std::endl;
    }
    char line[100] = {0};
    for (int i = 0; i < 100; i++)
    {
        const char msg[] = "String added successfully";
        fgets(line, sizeof(line), client1.get());
        BOOST_CHECK(!strcmp(msg, trim(line)));
        memset(line, 0, sizeof(line));
        fgets(line, sizeof(line), client2.get());
        BOOST_CHECK(!strcmp(msg, trim(line)));
        memset(line, 0, sizeof(line));
    }

    for (int i = 0; i < 100; i++)
    {
        std::string msg;

        msg = (boost::format("arr[%d]=\"str1%d\"") % i % i).str();
        fgets(line, sizeof(line), client1.get());
        trim(line);
        BOOST_CHECK(!strcmp(msg.c_str(), trim(line)));
        memset(line, 0, sizeof(line));

        msg = (boost::format("arr[%d]=\"str2%d\"") % i % i).str();
        fgets(line, sizeof(line), client2.get());
        trim(line);
        BOOST_CHECK(!strcmp(msg.c_str(), trim(line)));
        memset(line, 0, sizeof(line));
    }
    input1 << "exit" << std::endl;
    input2 << "exit" << std::endl;
    char s[100];
    while (fgets(s, 100, serv.get()) != NULL)
    {
        std::cout << s;
        memset(s, 0, 100);
    }
}