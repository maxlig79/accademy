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
  typedef boost::interprocess::basic_string<char, std::char_traits<char>, CharAllocator> stringIpc;
  message_queue::remove(MESSAGE_QUEUE_NAME.c_str());
  shared_memory_object::remove(SHARED_MEMORY_NAME.c_str());
  message_queue mq(create_only, MESSAGE_QUEUE_NAME.c_str(), MAX_MESSAGE_NUMBER, MAX_MESSAGE_SIZE);
  managed_shared_memory msm(create_only, SHARED_MEMORY_NAME.c_str(), SHARED_MEMORY_SIZE);
  message_queue::size_type recv_size;
  unsigned int priority;
  auto mutex = msm.find_or_construct<interprocess_mutex>(MUTEX_IPC_NAME.c_str())();
  auto condition = msm.find_or_construct<interprocess_condition>(COND_IPC_NAME.c_str())();
  try
  {
    while (strcmp(MQR.command, "EXIT") != 0)
    {
      mq.receive(&MQR, MAX_MESSAGE_SIZE, recv_size, priority);
      CommandPair commandPair = split_command(MQR.command);
      scoped_lock<interprocess_mutex> lock(*mutex);
      switch (commandPair.first)
      {
      case CommandIds::HELP:
      {
        msm.find_or_construct<stringIpc>(HELP_COMMAND.c_str())("Instructions:", msm.get_segment_manager());
        break;
      }
      case CommandIds::EXIT:
      {
        message_queue::remove(MESSAGE_QUEUE_NAME.c_str());
        shared_memory_object::remove(SHARED_MEMORY_NAME.c_str());
        break;
      }
      case CommandIds::ADD:
      {
        dynamicArray.addEntry(commandPair.second);
        stringIpc *s = msm.find_or_construct<stringIpc>(ADD_COMMAND.c_str())("Add OK", msm.get_segment_manager());
        cout << (*s) << endl;
        break;
      }
      case CommandIds::DELETE:
      {
        if (dynamicArray.deleteEntry(commandPair.second) == true)
        {
          msm.construct<stringIpc>(DELETE_COMMAND.c_str())("Delete OK", msm.get_segment_manager());
        }
        else
        {
          msm.construct<stringIpc>(DELETE_COMMAND.c_str())("Delete NOK", msm.get_segment_manager());
        }
        break;
      }
      default:
      {
        break;
      }
      }
      condition->notify_all();
    }
  }

  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }
  return 0;
}