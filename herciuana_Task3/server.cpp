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
  int nr_clients;
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
  std::map<int, std::shared_ptr<DynamicStringArray>> ClientArray;

  try
  {
    do
    {
      mq.receive(&MQR, MAX_MESSAGE_SIZE, recv_size, priority);
      if (ClientArray.find(MQR.ID_Client) == ClientArray.end())
      {
        ClientArray.insert(std::make_pair(MQR.ID_Client, std::make_unique<DynamicStringArray>()));
        nr_clients++;
      }
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
        if (nr_clients == 1)
        {
          message_queue::remove(MESSAGE_QUEUE_NAME.c_str());
          shared_memory_object::remove(SHARED_MEMORY_NAME.c_str());
        }
        nr_clients--;
        break;
      }
      case CommandIds::ADD:
      {
        ClientArray[MQR.ID_Client]->addEntry(commandPair.second);
        stringIpc *s = msm.find_or_construct<stringIpc>(ADD_COMMAND.c_str())("Add OK", msm.get_segment_manager());
        cout << (*s) << endl;
        break;
      }
      case CommandIds::DELETE:
      {
        if (ClientArray[MQR.ID_Client]->deleteEntry(commandPair.second) == true)
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
      case CommandIds::GET:
      {
        if (ClientArray[MQR.ID_Client]->getEntry(std::stoi(commandPair.second)))
        {
          msm.construct<stringIpc>(GET_COMMAND.c_str())((*ClientArray[MQR.ID_Client]->getEntry(std::stoi(commandPair.second))).c_str(), msm.get_segment_manager());
        }
        else
        {
          msm.construct<stringIpc>(GET_COMMAND.c_str())("Not found", msm.get_segment_manager());
        }
        break;
      }
      }
      condition->notify_one();
    } while (nr_clients != 0);
  }

  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }
  return 0;
}