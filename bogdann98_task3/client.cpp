#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <boost/asio.hpp>
#include "common.h"
#include <vector>
#include <cstring>
#include <cstdlib>
#include <string>


using namespace boost::interprocess;
using namespace std;
int main()
{
    MessageQueueRequest mqrstruct;   
    message_queue mq(open_only,MESSAGE_QUEUE_NAME.c_str());
    managed_shared_memory msh(open_only,SHARED_MEMORY_NAME.c_str());
    typedef boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager> CharAllocator; 
    typedef boost::interprocess::basic_string<char, std::char_traits<char>, CharAllocator> my_string;
    auto mutex_ipc = msh.find_or_construct<interprocess_mutex>(MUTEX_IPC.c_str())();
    auto condition_ipc = msh.find_or_construct<interprocess_condition>(IPC_CONDITION.c_str())();

    try
    {
        while(strcmp(mqrstruct.command,"exit")!=0)
        {
            cout<<"Insert a command "<<endl;
            cin>>mqrstruct.command;
            mq.send(&mqrstruct,MAX_MESSAGE_SIZE,0);

            CommandPair commandPair=split_command(mqrstruct.command);
            scoped_lock<interprocess_mutex> lock(*mutex_ipc);
            condition_ipc->wait(lock);
            

        switch(commandPair.first)
        {

        case CommandIds::EXIT:
        {
           
            message_queue::remove(MESSAGE_QUEUE_NAME.c_str());
            shared_memory_object::remove(SHARED_MEMORY_NAME.c_str());

            break;
        }
        case CommandIds::GET:
        {
            pair<my_string*,size_t>p=msh.find<my_string>(GET_COMMAND.c_str());
            cout<<p.first->c_str()<<endl;
            msh.destroy<my_string>(GET_COMMAND.c_str());
            break;
        }
         case CommandIds::DELETE:
        {
            pair<my_string*,size_t>p=msh.find<my_string>(DELETE_COMMAND.c_str());
            cout<<p.first->c_str()<<endl;
            msh.destroy<my_string>(DELETE_COMMAND.c_str());
            break;
        }
         case CommandIds::ADD:
        {
            
            pair<my_string*,size_t>p=msh.find<my_string>(ADD_COMMAND.c_str());
            cout<<p.first->c_str()<<endl;
            msh.destroy<my_string>(ADD_COMMAND.c_str());
            

            break;
        }
         case CommandIds::HELP:
        {
            pair<my_string*,size_t>p=msh.find<my_string>(HELP_COMMAND.c_str());
            cout<<p.first->c_str()<<endl;
            msh.destroy<my_string>(HELP_COMMAND.c_str());
            break;
        }

       
        }   
        }
    }
          catch (const std::exception &e)
            {
            cerr << e.what() << '\n';
            }

            return 0;
    }