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
  typedef boost::interprocess::basic_string<char, std::char_traits<char>, CharAllocator> stringIpc;

  message_queue mq(open_only, MESSAGE_QUEUE_NAME.c_str());

  managed_shared_memory msm(open_only, SHARED_MEMORY_NAME.c_str());

  auto mutex = msm.find_or_construct<interprocess_mutex>(MUTEX_IPC_NAME.c_str())();
  auto condition = msm.find_or_construct<interprocess_condition>(COND_IPC_NAME.c_str())();
  
  try
  {
    while (strcmp(MQR.command, "exit") != 0)
    {
      cout<<"Insert command:"<<endl;
      cin >> MQR.command;
      MQR.ID_Client = getpid();
      mq.send(&MQR, MAX_MESSAGE_SIZE, 0);
      CommandPair commandPair = split_command(MQR.command);
      scoped_lock<interprocess_mutex> lock(*mutex);
      condition->wait(lock);
      switch (commandPair.first)
      {
      case CommandIds::HELP:
      {
        std::pair<stringIpc *, size_t> p = msm.find<stringIpc>(HELP_COMMAND.c_str());
        if (p.first)
        {
          std::cout << p.first->c_str() << std::endl;
          for (auto itr = COMMAND_TO_HELP.begin(); itr != COMMAND_TO_HELP.end(); ++itr)
          {
            std::cout << itr->first << ": " << itr->second << std::endl;
          }
          std::cout << std::endl;
        }
        msm.destroy<stringIpc>(HELP_COMMAND.c_str());
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
        std::pair<stringIpc *, size_t> p = msm.find<stringIpc>(ADD_COMMAND.c_str());
        std::cout << p.first->c_str() << std::endl;
        msm.destroy<stringIpc>(ADD_COMMAND.c_str());
        break;
      }
      case CommandIds::DELETE:
      {
        std::pair<stringIpc *, size_t> p = msm.find<stringIpc>(DELETE_COMMAND.c_str());
        std::cout << p.first->c_str() << std::endl;
        msm.destroy<stringIpc>(DELETE_COMMAND.c_str());
        break;
      }
      case CommandIds::GET:
      {
        std::pair<stringIpc *, size_t> p = msm.find<stringIpc>(GET_COMMAND.c_str());
        std::cout << p.first->c_str() << std::endl;
        msm.destroy<stringIpc>(GET_COMMAND.c_str());
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