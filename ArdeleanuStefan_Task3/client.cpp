#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <iostream>
#include <memory>
#include <boost/asio.hpp>
#include "common.h"

using namespace boost::interprocess;

namespace Shared
{
   using Segment = managed_shared_memory;
   using Manager = Segment::segment_manager;

   using CharAllocator = allocator<char, Manager>;
   using String = basic_string<char, std::char_traits<char>, CharAllocator>;

   using StringAllocator = allocator<String, Manager>;
   using Vector = vector<String, StringAllocator>;
}

class Client
{
private:
   std::unique_ptr<message_queue> m_mq;
   std::unique_ptr<managed_shared_memory> m_managed_smh;

public:
   Client()
   {
      m_mq = std::make_unique<message_queue>(open_only, MESSAGE_QUEUE_NAME.c_str());
      m_managed_smh = std::make_unique<managed_shared_memory>(open_only, SHARED_MEMORY_NAME.c_str());
   }

   void start()
   {
      MessageQueueRequest msg;

      auto &mutex = *m_managed_smh->find_or_construct<interprocess_mutex>("mutex")();
      auto &cond = *m_managed_smh->find_or_construct<interprocess_condition>("cond")();

      while ((strcmp(msg.command, "exit") != 0))
      {
         std::cin >> msg.command;

         m_mq->send(&msg, sizeof(msg), 0);

         CommandPair command_pair = split_command(msg.command);

         scoped_lock<interprocess_mutex> lock(mutex);
         cond.wait(lock);
         
         switch (command_pair.first)
         {

         case CommandIds::HELP:
         {
            std::pair<Shared::Vector *, size_t> vec = m_managed_smh->find<Shared::Vector>("HELP");

            for(int i = 0; i < vec.first->size(); i = i+2) {
               std::cout << vec.first->at(i) << " " << vec.first->at(i+1) << std::endl;
            }

            m_managed_smh->destroy<Shared::Vector>("HELP");

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
            std::pair<Shared::String *, size_t> p = m_managed_smh->find<Shared::String>("ADD");
            std::cout << p.first->c_str() << std::endl;

            break;
         }

         case CommandIds::DELETE:
         {
            std::pair<Shared::String *, size_t> p = m_managed_smh->find<Shared::String>("DELETE");
            std::cout << p.first->c_str() << std::endl;

            m_managed_smh->destroy<Shared::String>("DELETE");

            break;
         }

         case CommandIds::GET:
         {
            std::pair<Shared::String *, size_t> p = m_managed_smh->find<Shared::String>("GET");
            std::cout << p.first->c_str() << std::endl;

            m_managed_smh->destroy<Shared::String>("GET");

            break;
         }

         default:
         {
            break;
         }
         }
      }
   }
};

int main()
{
   Client c;
   c.start();
   return 0;
}