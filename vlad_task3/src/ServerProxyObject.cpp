#include <cstdint>
#include <ServerProxyObject.hpp>
#include <boost/format.hpp>
#include <Common.hpp>
#include <iostream>
#include <signal.h>

using namespace common;

namespace server
{
    ServerProxyObject::ServerProxyObject(int max_clients) : ProxyBase(boost::interprocess::create_only),
                                                            max_clients(max_clients)
    {
    }

    ServerProxyObject::~ServerProxyObject()
    {
        setServerAvailable(false);
        clearSharedMemory();
    }

    void ServerProxyObject::setServerAvailable(bool value)
    {
        bool *available = shm->find_or_construct<bool>(_SERVER_AVAILABLE.c_str())(value);
        *available = value;
    }

    void ServerProxyObject::run()
    {
        uint8_t command;
        uint64_t recvd;
        uint32_t priority;
        setServerAvailable(true);
        while (active)
        {
            mq->receive(&command, sizeof(int), recvd, priority);
            if (arrs.find(getId()) == arrs.end() && arrs.size() == max_clients)
            {

                boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lk(*mem_mutex);
                setStatus(ERROR);
                cond->notify_all();
                continue;
            }
            switch (command)
            {
            case EXIT:
            {
                boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lk(*mem_mutex);
                int id = getId();
                arrs.erase(id);
                if(arrs.empty())
                {
                    stop();
                }
                setStatus(SUCCESS);
            }
            break;
            case ADD:
            {
                boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lk(*mem_mutex);
                int id = getId();
                arrs[id].addEntry(getValue());
                setStatus(SUCCESS);
            }
            break;
            case DELETE:
            {

                boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lk(*mem_mutex);
                std::string str = getValue();
                bool success = arrs[getId()].deleteEntry(str);
                setStatus(success ? SUCCESS : ERROR);
            }
            break;
            case HELP:
            {

                boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lk(*mem_mutex);
                arrs.insert(std::make_pair<int, DynamicArray>(getId(), DynamicArray()));
                setValue("add(str)\ndelete(str)\nget(int)\nexit\n");
                setStatus(SUCCESS);
            }
            break;
            case GET:
            {
                boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lk(*mem_mutex);
                int i = getIndex();
                try
                {
                    setValue(arrs[getId()].getEntry(i));
                    setStatus(SUCCESS);
                }
                catch (std::exception &e)
                {
                    setStatus(ERROR);
                }
            }
            break;
            default:
            {
                boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lk(*mem_mutex);
                setValue("Wrong command");
                setStatus(ERROR);
            }
            }
            cond->notify_all();
        }
    }

    void ServerProxyObject::stop()
    {
        active = false;
    }
}
