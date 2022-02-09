#ifndef CAT_PROXY_BASE_H_
#define CAT_PROXY_BASE_H_

#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <Common.hpp>
#include <memory>
#include <string>

namespace base
{
    class ProxyBase
    {
    protected:
        ProxyBase(boost::interprocess::open_only_t open_only);
        ProxyBase(boost::interprocess::create_only_t create_only);

    protected:
        std::unique_ptr<boost::interprocess::message_queue> mq;
        std::unique_ptr<boost::interprocess::managed_shared_memory> shm;
        std::unique_ptr<boost::interprocess::named_condition> id_cond;
        std::unique_ptr<boost::interprocess::named_mutex> proc_mutex;
        boost::interprocess::interprocess_mutex* mem_mutex;

    protected:
        std::string getValue();
        void setValue(const std::string &value);

        common::Status getStatus();
        void setStatus(common::Status value);

        int getIndex();
        void setIndex(int value);

        int getId();
        void setId(int value);

        boost::interprocess::interprocess_condition *getCondition(int index);

    public:
        int clearSharedMemory();
    };
}

#endif