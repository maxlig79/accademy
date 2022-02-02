#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <iostream>
#include <boost/asio.hpp>
#include "common.h"
#include "DynamicStringArray.hpp"

using namespace boost::interprocess;


int main()
{
  MessageQueueRequest mqStruct;
  DynamicStringArray dynamicArray;
  message_queue::remove(MESSAGE_QUEUE_NAME.c_str());
  shared_memory_object::remove(SHARED_MEMORY_NAME.c_str());
  message_queue mq(create_only, MESSAGE_QUEUE_NAME.c_str(), MAX_MESSAGE_NUMBER, MAX_MESSAGE_SIZE);
  unsigned int priority;
  message_queue::size_type recvd_size;

  typedef boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager> CharAllocator;
  typedef boost::interprocess::basic_string<char, std::char_traits<char>, CharAllocator> stringShared;
  managed_shared_memory managed_sm(create_only, SHARED_MEMORY_NAME.c_str(), SHARED_MEMORY_SIZE);
 
   
  try
  {
    while (strcmp(mqStruct.command, "exit") != 0)
    {
    mq.receive(&mqStruct, MAX_MESSAGE_SIZE, recvd_size, priority);
    stringShared *s =managed_sm.find_or_construct<stringShared>(ADD_COMMAND.c_str())("Add OK",managed_sm.get_segment_manager());
    cout<<(*s)<<endl;
    // cout<<mqStruct.command<<endl;
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }

  return 0;
}