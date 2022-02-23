#include "common.h"
class Client
{
public:
  void start()
  {
    MessageQueueRequest mqStruct;
    
    message_queue mq(open_only, MESSAGE_QUEUE_NAME.c_str());

    managed_shared_memory managedSm(open_only, SHARED_MEMORY_NAME.c_str());

    auto mutexIpc = managedSm.find_or_construct<interprocess_mutex>(MUTEX_IPC_NAME.c_str())();
    auto conditionIpc = managedSm.find_or_construct<interprocess_condition>(CONDITION_IPC_NAME.c_str())();

    try
    {
      while (strcmp(mqStruct.command, "exit") != 0)
      {
        // cout << "Insert command: " << endl;
        cin.getline(mqStruct.command, 100);

        scoped_lock<interprocess_mutex> lock(*mutexIpc);
        mqStruct.idClient = getpid();
        std::string strClient=std::to_string(mqStruct.idClient);

        mq.send(&mqStruct, MAX_MESSAGE_SIZE, 0);

        conditionIpc->wait(lock);
        CommandPair commandPair = split_command(mqStruct.command);

        switch (commandPair.first)
        {
        case CommandIds::HELP:
        {
          std::pair<SharedStringVector *, size_t> vec = managedSm.find<SharedStringVector>(HELP_COMMAND.c_str());

          for (int i = 0; i < vec.first->size(); i = i + 2)
          {
            cout << vec.first->at(i) << " " << vec.first->at(i + 1) << std::endl;
          }
          managedSm.destroy<SharedStringVector>(HELP_COMMAND.c_str());
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
          std::pair<SharedStringIpc *, std::size_t> ret = managedSm.find<SharedStringIpc>((ADD_COMMAND+ strClient).c_str());
          if (ret.second > 0)
          {
            cout << ret.first->c_str() << endl;
            managedSm.destroy<SharedStringIpc>((ADD_COMMAND+ strClient).c_str());
          }
          break;
        }
        case CommandIds::DELETE:
        {
          std::pair<SharedStringIpc *, std::size_t> ret = managedSm.find<SharedStringIpc>((DELETE_COMMAND+ strClient).c_str());
          cout << ret.first->c_str() << endl;
          managedSm.destroy<SharedStringIpc>((DELETE_COMMAND+ strClient).c_str());
          break;
        }
        case CommandIds::GET:
        {
          std::pair<SharedStringIpc *, std::size_t> ret = managedSm.find<SharedStringIpc>((GET_COMMAND+ strClient).c_str());
          if (ret.second > 0)
          {
            cout << ret.first->c_str() << endl;
            managedSm.destroy<SharedStringIpc>((GET_COMMAND+ strClient).c_str());
          }
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
  }
};
int main()
{
  Client client;
  client.start();
  return 0;
}