#ifndef CAT_PROXY_BASE_H_
#define CAT_PROXY_BASE_H_

#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <Common.hpp>
#include <string>

namespace base
{
    class ProxyBase
    {
    public:
        ProxyBase();
        
    protected:
        boost::interprocess::message_queue mq;
        boost::interprocess::managed_shared_memory shm;
        boost::interprocess::named_condition cond;
        boost::interprocess::named_mutex mutex;

        std::string getValue();
        void setValue(const std::string &value);
        
        common::Status getStatus();
        void setStatus(common::Status value);

        int getIndex();
        void setIndex(int value);
    };
}

#endif