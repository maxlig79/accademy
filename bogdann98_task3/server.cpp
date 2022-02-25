#include "DynamicStringArray.h"
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <iostream>
#include <boost/asio.hpp>
#include "common.h"
#include <string>

using namespace boost::interprocess;
using namespace std;
int main()
{
  std::map<int, std::shared_ptr<DynamicStringArray>> clientArray;
  DynamicStringArray dynamicArray;
  MessageQueueRequest mqrstruct;
  bool turn_on = true;
  message_queue::remove(MESSAGE_QUEUE_NAME.c_str());
  shared_memory_object::remove(SHARED_MEMORY_NAME.c_str());
  message_queue mq(create_only, MESSAGE_QUEUE_NAME.c_str(), MAX_MESSAGE_NUMBER, MAX_MESSAGE_SIZE);
  managed_shared_memory msh(create_only, SHARED_MEMORY_NAME.c_str(), SHARED_MEMORY_SIZE);
  unsigned priority;
  message_queue::size_type received_size;
  typedef boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager> CharAllocator;
  typedef boost::interprocess::basic_string<char, std::char_traits<char>, CharAllocator> my_string;

  auto mutex_ipc = msh.find_or_construct<interprocess_mutex>(MUTEX_IPC.c_str())();             // create a mutex
  auto condition_ipc = msh.find_or_construct<interprocess_condition>(IPC_CONDITION.c_str())(); // Create a condition variable

  try
  {
    while (turn_on == true)
    {
      mq.receive(&mqrstruct, MAX_MESSAGE_SIZE, received_size, priority);
      if (clientArray.find(mqrstruct.client) == clientArray.end())
      {
        clientArray.insert(std::make_pair(mqrstruct.client, std::make_unique<DynamicStringArray>()));
      }
      CommandPair commandPair = split_command(mqrstruct.command);
      scoped_lock<interprocess_mutex> lock(*mutex_ipc);

      switch (commandPair.first)
      {
      case CommandIds::EXIT:
      {

        message_queue::remove(MESSAGE_QUEUE_NAME.c_str());
        shared_memory_object::remove(SHARED_MEMORY_NAME.c_str());
        turn_on = false;
        break;
      }
      case CommandIds::GET:
      {
        // Index is correct
        if (clientArray[mqrstruct.client]->getEntry(stoi(commandPair.second)))
        {
          msh.find_or_construct<my_string>(GET_COMMAND.c_str())("Found", msh.get_segment_manager());
        }

        // Index is not correct
        else
        {
          msh.find_or_construct<my_string>(GET_COMMAND.c_str())("Not found", msh.get_segment_manager());
        }
        break;
      }
      case CommandIds::DELETE:
      {
        // Delete if the string exists
        if (clientArray[mqrstruct.client]->deleteEntry(commandPair.second))
        {
          msh.construct<my_string>(DELETE_COMMAND.c_str())("Delete OK", msh.get_segment_manager());
        }
        // Failed delete if the string doesn't exist
        else
        {
          msh.construct<my_string>(DELETE_COMMAND.c_str())("Delete not OK", msh.get_segment_manager());
        }

        break;
      }
      case CommandIds::ADD:
      {
        // Add a string and print "Add ok"
        clientArray[mqrstruct.client]->addEntry(commandPair.second);
        msh.construct<my_string>(ADD_COMMAND.c_str())("Add OK", msh.get_segment_manager());
        break;
      }
      case CommandIds::HELP:
      {
        msh.find_or_construct<my_string>(HELP_COMMAND.c_str())("Intructions: ", msh.get_segment_manager());

        break;
      }
      }
      condition_ipc->notify_one();
    }
  }
  catch (const std::exception &e)
  {
    cerr << e.what() << '\n';
  }

  return 0;
}