#include <ProxyBase.hpp>
#include <boost/format.hpp>
#include <iostream>
#include <limits>

using namespace common;

namespace base
{

    ProxyBase::ProxyBase(boost::interprocess::open_only_t open_only) : shm(std::make_unique<boost::interprocess::managed_shared_memory>(open_only, _SHM.c_str())),
                                                                       mq(std::make_unique<boost::interprocess::message_queue>(open_only, _MQ.c_str())),
                                                                       id_cond(std::make_unique<boost::interprocess::named_condition>(open_only, _COND.c_str())),
                                                                       proc_mutex(std::make_unique<boost::interprocess::named_mutex>(open_only, _PROC_MUTEX.c_str())),
                                                                       mem_mutex(shm->find<boost::interprocess::interprocess_mutex>(_MEM_MUTEX.c_str()).first)
    {
    }

    ProxyBase::ProxyBase(boost::interprocess::create_only_t create_only)
    {
        clearSharedMemory();
        shm = std::make_unique<boost::interprocess::managed_shared_memory>(create_only, _SHM.c_str(), UINT16_MAX);
        mq = std::make_unique<boost::interprocess::message_queue>(create_only, _MQ.c_str(), 10, sizeof(int));
        id_cond = std::make_unique<boost::interprocess::named_condition>(create_only, _COND.c_str());
        proc_mutex = std::make_unique<boost::interprocess::named_mutex>(create_only, _PROC_MUTEX.c_str());
        mem_mutex = shm->construct<boost::interprocess::interprocess_mutex>(_MEM_MUTEX.c_str())();
    }

    int ProxyBase::clearSharedMemory()
    {
        boost::interprocess::named_condition::remove(_COND.c_str());
        boost::interprocess::message_queue::remove(_MQ.c_str());
        boost::interprocess::shared_memory_object::remove(_SHM.c_str());
        boost::interprocess::named_mutex::remove(_PROC_MUTEX.c_str());
        return 0;
    }

    std::string ProxyBase::getValue()
    {
        std::pair<ShmString *, unsigned long> p = shm->find<ShmString>(VALUE.c_str());
        return std::string(p.first->c_str());
    }

    void ProxyBase::setValue(const std::string &value)
    {
        ShmString *str = shm->find_or_construct<ShmString>(VALUE.c_str())(value, shm->get_segment_manager());
        *str = value.c_str();
    }

    int ProxyBase::getIndex()
    {
        std::pair<int *, unsigned long> p = shm->find<int>(INDEX.c_str());
        return *p.first;
    }

    void ProxyBase::setIndex(int value)
    {
        int *index = shm->find_or_construct<int>(INDEX.c_str())(value);
        *index = value;
    }

    Status ProxyBase::getStatus()
    {
        std::pair<int *, unsigned long> p = shm->find<int>(RESULT.c_str());
        return (Status)(*p.first);
    }

    void ProxyBase::setStatus(Status value)
    {
        int *status = shm->find_or_construct<int>(RESULT.c_str())((int)value);
        *status = (int)value;
    }

    int ProxyBase::getId()
    {
        std::pair<int *, unsigned long> p = shm->find<int>(CLIENT_ID.c_str());
        return (Status)(*p.first);
    }

    void ProxyBase::setId(int value)
    {
        int *id = shm->find_or_construct<int>(CLIENT_ID.c_str())(value);
        *id = value;
    }

    boost::interprocess::interprocess_condition *ProxyBase::getCondition(int index)
    {
        using boost::interprocess::interprocess_condition;
        std::pair<interprocess_condition*, unsigned long> p = shm->find<interprocess_condition>(CONDITIONS.c_str());
        if(index >= p.second)
        {
            throw std::out_of_range("Condition index out of range");
        }
        return p.first + index;
    }
}