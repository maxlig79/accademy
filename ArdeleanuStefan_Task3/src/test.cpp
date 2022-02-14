#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>
#include "common.h"
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <utility>
#include <sys/types.h>
#include <sys/wait.h>
#include <thread>
#include <future>

bool
start_subprocess(char *const command[], int *pid, int *infd, int *outfd)
{
	int p1[2], p2[2];

	if (!pid || !infd || !outfd)
		return false;

	if (pipe(p1) == -1)
		goto err_pipe1;
	if (pipe(p2) == -1)
		goto err_pipe2;
	if ((*pid = fork()) == -1)
		goto err_fork;

	if (*pid) {
		/* Parent process. */
		*infd = p1[1];
		*outfd = p2[0];
		close(p1[0]);
		close(p2[1]);
		return true;
	} else {
		/* Child process. */
		dup2(p1[0], 0);
		dup2(p2[1], 1);
		close(p1[0]);
		close(p1[1]);
		close(p2[0]);
		close(p2[1]);
		execvp(*command, command);
		/* Error occured. */
		fprintf(stderr, "error running %s: %s", *command, strerror(errno));
		abort();
	}

err_fork:
	close(p2[1]);
	close(p2[0]);
err_pipe2:
	close(p1[1]);
	close(p1[0]);
err_pipe1:
	return false;
}

struct DataReceiver
{
    void operator()(int outfd, int infd)
    {
        ssize_t n;
        char buf[128];
        memset(buf, 0, 128);
		int counter = 0;

		std::cout << "read before " << std::endl;
        while (n = read(outfd, buf, sizeof(buf)))
        {
            std::cout << "buf: " << buf << std::endl;
            std::cout << "n: " << n << std::endl;
            memset(buf, 0, 128);
			counter++;
			if (counter == 5)
			{
				break;
			}
        }

		//close(infd);
		//close(outfd);
    }
};

BOOST_AUTO_TEST_CASE( my_test )
{
    int infd;
	int outfd;
    int infd2;
	int outfd2;
    pid_t pid;
    ssize_t n;
    int expectedResponse = 0;
    char msg[128] = "add;max\nadd;is\nadd;good\nget;1\n";
    //char msg[128];
    char buf[128];
    std::promise<int> data;
    char* arg[] = {"/home/projectx/github/stefan/accademy/ArdeleanuStefan_Task3/build/client", NULL};


	if (!start_subprocess(arg, &pid, &infd, &outfd))
    {
        std::cout << "start_subprocess failed!" << std::endl;
		exit(1);
	}

	std::future<void> result = std::async(DataReceiver(), outfd, infd);

    //memset(msg, 0, 128);
    //snprintf(msg, strlen("add;max\nadd;is\nadd;good\nget;1\n")+1, "add;max\nadd;is\nadd;good\nget;1\n");
	//usleep(500000);
    std::cout << "write before " << std::endl;
    write(infd, msg, sizeof(msg));
    std::cout << "write after " << std::endl;

	//close(outfd);
	//close(infd);
}