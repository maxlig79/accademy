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
  managed_shared_memory managedSm(open_only, SHARED_MEMORY_NAME.c_str());

  auto mutexIpc = managedSm.find_or_construct<interprocess_mutex>(MUTEX_IPC_NAME.c_str())();
  auto conditionIpc = managedSm.find_or_construct<interprocess_condition>(CONDITION_IPC_NAME.c_str())();
  try
  {
    while (strcmp(mqStruct.command, "exit") != 0)
    {
      cout << "Insert command: " << endl;
      cin >> mqStruct.command;
      mq.send(&mqStruct, MAX_MESSAGE_SIZE, 0);
      CommandPair commandPair = split_command(mqStruct.command);

      scoped_lock<interprocess_mutex> lock(*mutexIpc);
      conditionIpc->wait(lock);

      switch (commandPair.first)
      {
      case CommandIds::EXIT:
      {
        message_queue::remove(MESSAGE_QUEUE_NAME.c_str());
        shared_memory_object::remove(SHARED_MEMORY_NAME.c_str());
        break;
      }
      case CommandIds::ADD:
      {
        std::pair<stringShared *, std::size_t> ret = managedSm.find<stringShared>(ADD_COMMAND.c_str());
        cout << ret.first->c_str()<<endl;
        managedSm.destroy<stringShared>(ADD_COMMAND.c_str());
        break;
      }
      case CommandIds::DELETE:
      {
        std::pair<stringShared *, std::size_t> ret = managedSm.find<stringShared>(DELETE_COMMAND.c_str());
        cout << ret.first->c_str() << endl;
        managedSm.destroy<stringShared>(DELETE_COMMAND.c_str());
        break;
      }
      case CommandIds::GET:
      {
        std::pair<stringShared *, std::size_t> ret = managedSm.find<stringShared>(GET_COMMAND.c_str());
        cout << ret.first->c_str() << endl;
        managedSm.destroy<stringShared>(GET_COMMAND.c_str());
        break;
      }
      }
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