#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <iostream>
#include <boost/asio.hpp>
#include "common.h"
#include <iostream>

using namespace boost::interprocess;
using namespace std;
int main()
{
  MessageQueueRequest MQR;
  typedef boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager> CharAllocator;
  typedef boost::interprocess::basic_string<char, std::char_traits<char>, CharAllocator> string;
  message_queue mq(open_only, MESSAGE_QUEUE_NAME.c_str());

  managed_shared_memory msm(open_only, SHARED_MEMORY_NAME.c_str());
  try
  {
    while (strcmp(MQR.command, "exit") != 0)
    {
      cin>>MQR.command;
      mq.send(&MQR, MAX_MESSAGE_SIZE, 0);
      std::pair<string *, std::size_t> ret = msm.find<string>(ADD_COMMAND.c_str());
    }
  }
  catch (const std::exception &e)
  {
    message_queue::remove(MESSAGE_QUEUE_NAME.c_str());

    std::cerr << e.what() << '\n';
  }
  message_queue::remove(MESSAGE_QUEUE_NAME.c_str());
  return 0;
}
