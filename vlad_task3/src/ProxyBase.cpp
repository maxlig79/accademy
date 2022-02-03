#include <ProxyBase.hpp>

using namespace common;

namespace base
{

    ProxyBase::ProxyBase() : shm(boost::interprocess::managed_shared_memory(boost::interprocess::open_only, _SHM.c_str())),
                             mq(boost::interprocess::message_queue(boost::interprocess::open_only, _MQ.c_str())),
                             cond(boost::interprocess::named_condition(boost::interprocess::open_only, _COND.c_str())),
                             mutex(boost::interprocess::named_mutex(boost::interprocess::open_only, _MUTEX.c_str()))
    {
    }

    std::string ProxyBase::getValue()
    {
        std::pair<ShmString *, unsigned long> p = shm.find<ShmString>(VALUE.c_str());
        return std::string(p.first->c_str());
    }

    void ProxyBase::setValue(const std::string &value)
    {
        ShmString *str = shm.find_or_construct<ShmString>(VALUE.c_str())(value, shm.get_segment_manager());
        *str = value.c_str();
    }

    int ProxyBase::getIndex()
    {
        std::pair<int *, unsigned long> p = shm.find<int>(INDEX.c_str());
        return *p.first;
    }

    void ProxyBase::setIndex(int value)
    {
        int *index = shm.find_or_construct<int>(INDEX.c_str())(value);
        *index = value;
    }

    Status ProxyBase::getStatus()
    {
        std::pair<int *, unsigned long> p = shm.find<int>(RESULT.c_str());
        return (Status)(*p.first);
    }

    void ProxyBase::setStatus(Status value)
    {
        int *status = shm.find_or_construct<int>(RESULT.c_str())((int)value);
        *status = (int)value;
    }
}