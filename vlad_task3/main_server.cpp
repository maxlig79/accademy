#include <iostream>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/format.hpp>
#include <Common.hpp>
#include <DynamicArray.hpp>

using namespace common;

DynamicArray arr;
std::string getShmString(boost::interprocess::managed_shared_memory &shm, std::string name)
{
    std::pair<ShmString *, unsigned long> p = shm.find<ShmString>(name.c_str());
    return std::string(p.first->c_str());
}

void setResult(boost::interprocess::managed_shared_memory &shm, int result)
{
    int *res = shm.find_or_construct<int>(RESULT.c_str())(result);
    *res = result;
}
int main()
{
    boost::interprocess::named_condition::remove(_COND.c_str());
    boost::interprocess::message_queue::remove(_MQ.c_str());
    boost::interprocess::shared_memory_object::remove(_SHM.c_str());
    boost::interprocess::named_mutex::remove(_MUTEX.c_str());

    boost::interprocess::named_mutex mutex(boost::interprocess::create_only, _MUTEX.c_str());
    boost::interprocess::message_queue mq(boost::interprocess::create_only, _MQ.c_str(), 10, sizeof(int));
    boost::interprocess::managed_shared_memory shm(boost::interprocess::create_only, _SHM.c_str(), 1024);
    boost::interprocess::named_condition cond(boost::interprocess::create_only, _COND.c_str());
    uint8_t command;
    uint64_t recvd;
    uint32_t priority;
    while (true)
    {
        mq.receive(&command, sizeof(int), recvd, priority);
        //Same reason as in main_client.cpp
        switch (command)
        {
        case EXIT:
        {
            exit(0);
        }
        break;
        case ADD:
        {
            std::cout << "Received add" << std::endl;
            {
                boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lk(mutex);
                arr.addEntry(getShmString(shm, VALUE));
                setResult(shm, SUCCESS);
            }
            std::cout << "notify..." << std::endl;
            cond.notify_all();
        }
        break;
        case DELETE:
        {
            {
                boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lk(mutex);
                std::string str = getShmString(shm, VALUE);
                bool success = arr.deleteEntry(str);
                setResult(shm, success ? SUCCESS : ERROR);
            }
            cond.notify_all();
        }
        break;
        case HELP:
        {
            {
                boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lk(mutex);
                boost::format fmt("%d - add(str)\n%d - delete(str)\n%d - get(int)\n%d - exit\n");
                std::string help = (fmt % ADD % DELETE % GET % EXIT).str();
                ShmString *shm_str = shm.find_or_construct<ShmString>(VALUE.c_str())(help.c_str(), shm.get_segment_manager());
                *shm_str = help.c_str();
            }
            cond.notify_all();
        }
        break;
        case GET:
        {
            std::cout << "Received get" << std::endl;
            {
                boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lk(mutex);
                std::pair<int *, unsigned long> p = shm.find<int>(INDEX.c_str());
                int *idx = p.first;
                int i = *idx;
                try
                {
                    std::string str = arr.getEntry(i);
                    ShmString *shm_str = shm.find_or_construct<ShmString>(VALUE.c_str())(str.c_str(), shm.get_segment_manager());
                    *shm_str = str.c_str();
                    setResult(shm, SUCCESS);
                }
                catch (std::exception &e)
                {
                    setResult(shm, ERROR);
                }
            }
            std::cout << "notify..." << std::endl;
            cond.notify_all();
        }
        }
        }
}