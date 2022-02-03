#include <ClientProxyObject.hpp>
#include <iostream>

using namespace common;
ClientProxyObject::ClientProxyObject() : shm(boost::interprocess::managed_shared_memory(boost::interprocess::open_only, _SHM.c_str())),
                                         mq(boost::interprocess::message_queue(boost::interprocess::open_only, _MQ.c_str())),
                                         cond(boost::interprocess::named_condition(boost::interprocess::open_only, _COND.c_str())),
                                         mutex(boost::interprocess::named_mutex(boost::interprocess::open_only, _MUTEX.c_str()))
{
}

bool ClientProxyObject::addString(const std::string &str)
{
    boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lk(mutex);
    setValue(str);
    int code = ADD;
    mq.send(&code, sizeof(int), 0);
    cond.wait(lk);
    return success();
}

bool ClientProxyObject::deleteString(const std::string &str)
{
    boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lk(mutex);
    setValue(str);
    int code = DELETE;
    mq.send(&code, sizeof(int), 0);
    cond.wait(lk);
    return success();
}

void ClientProxyObject::exit()
{
    int code = EXIT;
    mq.send(&code, sizeof(int), 0);
}

std::string ClientProxyObject::get(int index, bool &has_string)
{
    boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lk(mutex);
    setIndex(index);
    int code = GET;
    mq.send(&code, sizeof(int), 0);
    cond.wait(lk);
    has_string = success();
    if(!has_string)
    {
        return "";
    }
    return getValue();
}

void ClientProxyObject::printHelp()
{
    boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lk(mutex);
    int code = HELP;
    mq.send(&code, sizeof(int), 0);
    cond.wait(lk);
    std::cout << getValue();
}

void ClientProxyObject::setValue(const std::string &value)
{
    ShmString *str = shm.find_or_construct<ShmString>(VALUE.c_str())(value, shm.get_segment_manager());
    *str = value.c_str();
}

std::string ClientProxyObject::getValue()
{
    std::pair<ShmString *, unsigned long> p = shm.find<ShmString>(VALUE.c_str());
    return std::string(p.first->c_str());
}

void ClientProxyObject::setIndex(int value)
{
    int *index = shm.find_or_construct<int>(INDEX.c_str())(value);
    *index = value;
}

bool ClientProxyObject::success()
{
    std::pair < int *, unsigned long> p = shm.find<int>(RESULT.c_str());
    return *p.first == SUCCESS;
}

/* void setSharedMemory(boost::interprocess::managed_shared_memory &shm, std::string name, std::string value)
{
    ShmString *str = shm.find_or_construct<ShmString>(name.c_str())(ShmString(value.c_str()), shm.get_segment_manager());
    *str = value.c_str();
} */