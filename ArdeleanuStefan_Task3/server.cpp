#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <iostream>
#include <boost/asio.hpp>
#include <DynamicStringArray.hpp>
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

class Server
{
private:
   DynamicStringArray m_string_array;
   std::unique_ptr<message_queue> m_mq;
   std::unique_ptr<managed_shared_memory> m_managed_smh;

public:
   Server()
   {
      shared_memory_object::remove(SHARED_MEMORY_NAME.c_str());
      message_queue::remove(MESSAGE_QUEUE_NAME.c_str());

      m_mq = std::make_unique<message_queue>(create_only, MESSAGE_QUEUE_NAME.c_str(), MAX_MESSAGE_NUMBER, MAX_MESSAGE_SIZE);
      m_managed_smh = std::make_unique<managed_shared_memory>(create_only, SHARED_MEMORY_NAME.c_str(), SHARED_MEMORY_SIZE);
   }

   void start()
   {
      unsigned int priority;
      message_queue::size_type recvd_size;
      MessageQueueRequest msg;

      auto &mutex = *m_managed_smh->find_or_construct<interprocess_mutex>("mutex")();
      auto &cond = *m_managed_smh->find_or_construct<interprocess_condition>("cond")();

      while (strcmp(msg.command, "exit") != 0)
      {
         m_mq->receive(&msg, sizeof(msg), recvd_size, priority);

         CommandPair command_pair = split_command(msg.command);

         scoped_lock<interprocess_mutex> lock(mutex);

         switch (command_pair.first)
         {

         case CommandIds::HELP:
         {
            Shared::Vector *vec = m_managed_smh->find_or_construct<Shared::Vector>("HELP")(m_managed_smh->get_allocator<Shared::StringAllocator>());
            
            for (auto &cmd : COMMAND_TO_HELP)
            {
               vec->push_back(Shared::String(cmd.first.begin(), cmd.first.end(), m_managed_smh->get_segment_manager()));
               vec->push_back(Shared::String(cmd.second.begin(), cmd.second.end(), m_managed_smh->get_segment_manager()));
            }

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
            m_string_array.addEntry(command_pair.second);
            m_managed_smh->find_or_construct<Shared::String>("ADD")("Add OK", m_managed_smh->get_segment_manager());

            break;
         }

         case CommandIds::DELETE:
         {
            if (m_string_array.deleteEntry(command_pair.second))
            {
               m_managed_smh->construct<Shared::String>("DELETE")("DELETE OK", m_managed_smh->get_segment_manager());
            }
            else
            {
               m_managed_smh->construct<Shared::String>("DELETE")("DELETE NOT OK", m_managed_smh->get_segment_manager());
            }

            break;
         }

         case CommandIds::GET:
         {
            if (m_string_array.getEntry(std::stoi(command_pair.second)))
            {
               m_managed_smh->construct<Shared::String>("GET")((*m_string_array.getEntry(std::stoi(command_pair.second))).c_str(), m_managed_smh->get_segment_manager());
            }
            else
            {
               m_managed_smh->construct<Shared::String>("GET")("NOT FOUND", m_managed_smh->get_segment_manager());
            }

            break;
         }

         default:
         {
            break;
         }
         }
         
         cond.notify_one();
      }
   }
};

int main()
{
   Server s;
   s.start();
   return 0;
}