#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <iostream>
#include <boost/asio.hpp>
#include "common.h"
#include <boost/interprocess/allocators/allocator.hpp>
#include "DynamicStringArray.hpp"

using namespace boost::interprocess;

int main()
{
  MessageQueueRequest MQR;
  DynamicStringArray dynamicArray;
  typedef boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager> CharAllocator;
  typedef boost::interprocess::basic_string<char, std::char_traits<char>, CharAllocator> string;
  message_queue::remove(MESSAGE_QUEUE_NAME.c_str());
  shared_memory_object::remove(SHARED_MEMORY_NAME.c_str());
  message_queue mq(create_only, MESSAGE_QUEUE_NAME.c_str(), MAX_MESSAGE_NUMBER, MAX_MESSAGE_SIZE);
  managed_shared_memory msm(create_only, SHARED_MEMORY_NAME.c_str(), SHARED_MEMORY_SIZE);
  message_queue::size_type recv_size;
  unsigned int priority;
    try
  {
    while (strcmp(MQR.command, "exit") != 0)
    {
      mq.receive(&MQR, MAX_MESSAGE_SIZE, recv_size, priority);
      string *s = msm.find_or_construct<string>(ADD_COMMAND.c_str())("ADD OK", msm.get_segment_manager());
      cout<<(*s)<<endl;
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }
  return 0;
}