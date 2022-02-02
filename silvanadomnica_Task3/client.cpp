#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <iostream>
#include <boost/asio.hpp>
#include "common.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace boost::interprocess;

int main()
{

  MessageQueueRequest mqStruct;
  message_queue mq(open_only, MESSAGE_QUEUE_NAME.c_str());

  typedef boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager> CharAllocator;
  typedef boost::interprocess::basic_string<char, std::char_traits<char>, CharAllocator> stringShared;
  managed_shared_memory managed_sm(open_only, SHARED_MEMORY_NAME.c_str());
  try
  {
    while (strcmp(mqStruct.command, "exit") != 0)
    {
      cin >> mqStruct.command;
      mq.send(&mqStruct, MAX_MESSAGE_SIZE, 0);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      std::pair<stringShared *, std::size_t> ret =managed_sm.find<stringShared>(ADD_COMMAND.c_str());
      cout<<ret.first->c_str()<<endl;
      // switch (expression)
      // {
      // case /* constant-expression */:
      //   /* code */
      //   break;
      
      // default:
      //   break;
      // }
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