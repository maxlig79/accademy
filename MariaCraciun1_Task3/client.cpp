
#include "common.h"

class Client
{
  private:
      
  public:
    Client() 
    {

    }

  void start() 
  {

  }

};

int main()
{
  //Client client;
  //client.start();

  //Client
    MessageQueueRequest msgCmd;
  try
  {

  std::cout<<"add command"<<std::endl;
  std::cin >> msgCmd.command;
    std::cout<<std::endl<<sizeof(msgCmd)<<std::endl;
  message_queue msgQ (open_only, MESSAGE_QUEUE_NAME.c_str());
  msgQ.send (&msgCmd, MAX_MESSAGE_SIZE, 0);
  
  message_queue::remove(MESSAGE_QUEUE_NAME.c_str());

  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  return 0;
}