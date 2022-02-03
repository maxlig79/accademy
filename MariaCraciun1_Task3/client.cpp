
#include "common.h"

class Client
{
  public:

  void start() 
  {

    message_queue msgQ (open_only, MESSAGE_QUEUE_NAME.c_str(),MAX_MESSAGE_NUMBER, MAX_MESSAGE_SIZE );
    managed_shared_memory msgShm (open_only,SHARED_MEMORY_NAME.c_str(), SHARED_MEMORY_SIZE );

    MessageQueueRequest msgCmd;

    auto mutex = msgShm.find_or_construct<interprocess_mutex>(MUTEX_IPC.c_str())();
    auto condition = msgShm.find_or_construct<interprocess_condition>(CONDITION_IPC.c_str())();

    while ((strcmp(msgCmd.command, "exit") != 0))
  {
    std::cout<<"Add command:"<<std::endl;
    std::cin >> msgCmd.command;
    
    msgQ.send (&msgCmd, MAX_MESSAGE_SIZE, 0);
    CommandPair commandPair = split_command(msgCmd.command);

    scoped_lock<interprocess_mutex> lock (*mutex);
    condition->wait(lock);

      switch(commandPair.first)
      {
        case CommandIds::EXIT:
        {
          message_queue::remove(MESSAGE_QUEUE_NAME.c_str());
          shared_memory_object::remove(SHARED_MEMORY_NAME.c_str());
        break;
        }

        case CommandIds::ADD:
        {
          std::pair<MyStringAllocator*, size_t> p = msgShm.find<MyStringAllocator>("ADD");
          std::cout << p.first << std::endl;

          msgShm.destroy <MyStringAllocator> ("ADD");
        break;
        }
        
        case CommandIds::DELETE:
        {
          std::pair<MyStringAllocator*, size_t> p = msgShm.find<MyStringAllocator>("DELETE");
          std::cout << p.first << std::endl;

          msgShm.destroy <MyStringAllocator> ("DELETE");
        break;
        }
        
        case CommandIds::GET:
        {
          std::pair<MyStringAllocator*, size_t> p = msgShm.find<MyStringAllocator>("GET");
          std::cout << p.first << std::endl;

          msgShm.destroy <MyStringAllocator> ("GET");
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