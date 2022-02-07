#include "common.h"
#include "DynamicStringArray.hpp"

int main()
{
  MessageQueueRequest mqStruct;
  DynamicStringArray dynamicArray;

  message_queue::remove(MESSAGE_QUEUE_NAME.c_str());
  shared_memory_object::remove(SHARED_MEMORY_NAME.c_str());

  message_queue mq(create_only, MESSAGE_QUEUE_NAME.c_str(), MAX_MESSAGE_NUMBER, MAX_MESSAGE_SIZE);

  unsigned int priority;
  message_queue::size_type recvd_size;

  managed_shared_memory managedSm(create_only, SHARED_MEMORY_NAME.c_str(), SHARED_MEMORY_SIZE);

  auto mutexIpc = managedSm.find_or_construct<interprocess_mutex>(MUTEX_IPC_NAME.c_str())();
  auto conditionIpc = managedSm.find_or_construct<interprocess_condition>(CONDITION_IPC_NAME.c_str())();

  try
  {
    while (strcmp(mqStruct.command, EXIT_COMMAND.c_str()) != 0)
    {
      mq.receive(&mqStruct, MAX_MESSAGE_SIZE, recvd_size, priority);
      CommandPair commandPair = split_command(mqStruct.command);

      scoped_lock<interprocess_mutex> lock(*mutexIpc);

      switch (commandPair.first)
      {
      case CommandIds::HELP:
      {
        SharedStringVector *vec = managedSm.find_or_construct<SharedStringVector>(HELP_COMMAND.c_str())(managedSm.get_allocator<StringAllocator>());

        for (auto &cmd : COMMAND_TO_HELP)
        {
          vec->push_back(SharedStringIpc(cmd.first.begin(), cmd.first.end(), managedSm.get_segment_manager()));
          vec->push_back(SharedStringIpc(cmd.second.begin(), cmd.second.end(), managedSm.get_segment_manager()));
        }
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
        managedSm.find_or_construct<SharedStringIpc>(ADD_COMMAND.c_str())("Add OK", managedSm.get_segment_manager());
        break;
      }
      case CommandIds::DELETE:
      {
        if (dynamicArray.deleteEntry(commandPair.second))
        {
          managedSm.construct<SharedStringIpc>(DELETE_COMMAND.c_str())("DELETE OK", managedSm.get_segment_manager());
        }
        else
        {
          managedSm.construct<SharedStringIpc>(DELETE_COMMAND.c_str())("DELETE NOT OK", managedSm.get_segment_manager());
        }
        break;
      }
      case CommandIds::GET:
      {
        if (dynamicArray.getEntry(std::stoi(commandPair.second)))
        {
          managedSm.construct<SharedStringIpc>(GET_COMMAND.c_str())((*dynamicArray.getEntry(std::stoi(commandPair.second))).c_str(), managedSm.get_segment_manager());
        }
        else
        {
          managedSm.construct<SharedStringIpc>(GET_COMMAND.c_str())("Element not found", managedSm.get_segment_manager());
        }
        break;
      }
      }
      conditionIpc->notify_all();
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }

  return 0;
}