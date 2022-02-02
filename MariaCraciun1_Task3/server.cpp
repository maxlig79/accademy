#include "common.h"

class Server 
{
  private:

  public:
  Server() 
  {

  }

  void start()
  {

  }

};

int main()
{
  //Server server;
  //server.start();

  //Server
  MessageQueueRequest msgCmd;
  unsigned int priority;
  message_queue::size_type recvd_size;
  try
  {
   message_queue::remove("message_queue");
  message_queue msgQ (open_or_create, MESSAGE_QUEUE_NAME.c_str(),MAX_MESSAGE_NUMBER, MAX_MESSAGE_SIZE );

   while ((strcmp(msgCmd.command, "exit") != 0))
  {
  msgQ.receive (&msgCmd, sizeof(msgCmd), recvd_size, priority);
  if(sizeof(msgCmd)== recvd_size){
    std::cout<<"communication succeded"<< std::endl;
    return 1;
  }
  }
  }
   catch(interprocess_exception &ex){
      std::cout << ex.what() << std::endl;
      return 1;
   }
  message_queue::remove(MESSAGE_QUEUE_NAME.c_str());
  return 0;
}