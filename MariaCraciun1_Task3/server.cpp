#include "common.h"

class Server 
{
  public:
  Server() 
  {
    message_queue::remove (MESSAGE_QUEUE_NAME.c_str());
    shared_memory_object::remove (SHARED_MEMORY_NAME.c_str());
  }
  
  void start()
  {
    int clientNumber = 0;
    bool serverRunning = true;
    std::map <int, std::shared_ptr<DynamicStringArray>> clientsArray;
    message_queue msgQ (open_or_create, MESSAGE_QUEUE_NAME.c_str(),MAX_MESSAGE_NUMBER, MAX_MESSAGE_SIZE);
    managed_shared_memory msgShm (open_or_create,SHARED_MEMORY_NAME.c_str(), SHARED_MEMORY_SIZE);

    DynamicStringArray stringArray;
    MessageQueueRequest msgCmd;
    message_queue::size_type recvd_size;
    unsigned int priority;

   auto mutex = msgShm.find_or_construct <interprocess_mutex> (MUTEX_IPC.c_str()) ();
   auto condition = msgShm.find_or_construct <interprocess_condition> (CONDITION_IPC.c_str()) ();
   
   while ( serverRunning == true )
   {
      msgQ.receive (&msgCmd, sizeof(msgCmd), recvd_size, priority);

      if(clientsArray.find(msgCmd.clientID) == clientsArray.end())
      {
        clientsArray.insert(std::make_pair(msgCmd.clientID, std::make_unique<DynamicStringArray>() ) );
        clientNumber++;
      }
      CommandPair commandPair = split_command (msgCmd.command);
  
      scoped_lock <interprocess_mutex> lock (*mutex);

      switch (commandPair.first)
      {
        case CommandIds::HELP:
        {
          MyVectorAllocator *myVector = msgShm.find_or_construct <MyVectorAllocator> (HELP_COMMAND.c_str()) 
          (msgShm.get_allocator<StringAllocator>());
          for ( auto &itr : COMMAND_TO_HELP)
          {
            myVector->push_back(MyStringAllocator(itr.first.begin(), itr.first.end(), msgShm.get_segment_manager()));
            myVector->push_back(MyStringAllocator(itr.second.begin(), itr.second.end(), msgShm.get_segment_manager()));
          }
        break;
        }

        case CommandIds::EXIT:
        {
          if(clientNumber == 1)
          {
            message_queue::remove(MESSAGE_QUEUE_NAME.c_str());
            shared_memory_object::remove(SHARED_MEMORY_NAME.c_str());
            serverRunning = false;
          }
          
          clientNumber--; 
        break;
        }
        
        case CommandIds::ADD:
        {
          clientsArray[msgCmd.clientID] -> addEntry (commandPair.second);
          msgShm.find_or_construct <MyStringAllocator> (ADD_COMMAND.c_str()) 
          ("Add ok",msgShm.get_segment_manager());
        break;
        }
        
        case CommandIds::DELETE:
        {
          if (clientsArray[msgCmd.clientID] -> deleteEntry (commandPair.second) == true)
          {
            msgShm.construct <MyStringAllocator> (DELETE_COMMAND.c_str()) 
            ("Delete ok",msgShm.get_segment_manager());
          } else {
            msgShm.construct <MyStringAllocator> (DELETE_COMMAND.c_str()) 
            ("Delete not ok",msgShm.get_segment_manager());
          }
        break;
        }
        
        case CommandIds::GET:
        {
          if (clientsArray[msgCmd.clientID] -> getEntry(std::stoi(commandPair.second)))
          {
            msgShm.construct <MyStringAllocator> (GET_COMMAND.c_str()) 
            ((*clientsArray[msgCmd.clientID] -> getEntry (std::stoi(commandPair.second))).c_str(), msgShm.get_segment_manager());
          } else {
            msgShm.construct <MyStringAllocator> (GET_COMMAND.c_str()) 
            ("Element not found",msgShm.get_segment_manager() );
          }
        break;
        }

        default: { break; }
      }
      condition->notify_one();
   } 
  }

};

int main()
{
  Server server;
  server.start();
  
  return 0;
}