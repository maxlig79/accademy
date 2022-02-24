
#include "common.h"

class Client
{
  public:

  void start() 
  {
    message_queue msgQ (open_only, MESSAGE_QUEUE_NAME.c_str());
    managed_shared_memory msgShm (open_only,SHARED_MEMORY_NAME.c_str());

    auto mutex = msgShm.find_or_construct<interprocess_mutex> (MUTEX_IPC.c_str())();
    auto condition = msgShm.find_or_construct<interprocess_condition> (CONDITION_IPC.c_str())();

    while ((strcmp(msgCmd.command, EXIT_COMMAND.c_str()) != 0))
    {

      msgCmd.clientID = getpid();
      std::cin.getline(msgCmd.command, 100);

      scoped_lock <interprocess_mutex> lock (*mutex);

      msgQ.send (&msgCmd, MAX_MESSAGE_SIZE, 0);

      CommandPair commandPair = split_command (msgCmd.command);
      
      condition->wait (lock);
      
      switch (commandPair.first)
      {
        case CommandIds::HELP:
        {
          std::pair <MyVectorAllocator*, size_t> myVectorPair = msgShm.find <MyVectorAllocator> ((HELP_COMMAND + std::to_string(msgCmd.clientID)).c_str());
          
          for (int i=0; i< myVectorPair.first->size(); i+=2)
          {
            std::cout << myVectorPair.first->at(i) << ": "<< myVectorPair.first->at(i+1) << std::endl;
          }
          msgShm.destroy <MyVectorAllocator> ((HELP_COMMAND + std::to_string(msgCmd.clientID)).c_str());
        break;
        }

        case CommandIds::EXIT:
        {
          message_queue::remove (MESSAGE_QUEUE_NAME.c_str());
          shared_memory_object::remove (SHARED_MEMORY_NAME.c_str());
        break;
        }

        case CommandIds::ADD:
        {
          std::pair <MyStringAllocator*, size_t> p = msgShm.find<MyStringAllocator> ((ADD_COMMAND + std::to_string(msgCmd.clientID)).c_str());
          if(p.second > 0 )
          {
            std::cout << p.first->c_str() << std::endl;
            msgShm.destroy <MyStringAllocator> ((ADD_COMMAND + std::to_string(msgCmd.clientID)).c_str());
          }
        break;
        }
        
        case CommandIds::DELETE:
        {
          std::pair <MyStringAllocator*, size_t> p = msgShm.find<MyStringAllocator> ((DELETE_COMMAND + std::to_string(msgCmd.clientID)).c_str());
          if(p.second > 0 )
          {
            std::cout << p.first->c_str() << std::endl;
            msgShm.destroy <MyStringAllocator> ((DELETE_COMMAND + std::to_string(msgCmd.clientID)).c_str());
          }
        break;
        }
        
        case CommandIds::GET:
        {
          std::pair <MyStringAllocator*, size_t> p = msgShm.find<MyStringAllocator>((GET_COMMAND + std::to_string(msgCmd.clientID)).c_str());
          if(p.second >0 )
          {
            std::cout << p.first->c_str() << std::endl;
            msgShm.destroy <MyStringAllocator> ((GET_COMMAND + std::to_string(msgCmd.clientID)).c_str());
          }
        break;
        }

        default: { break; }
      }
     } 
    }
};

int main()
{
  Client client;
  client.start();

  return 0;
}