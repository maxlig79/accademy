#include <cstdint>
#include <ServerProxyObject.hpp>
#include <boost/format.hpp>
#include <Common.hpp>

using namespace common;

namespace server
{
    ServerProxyObject::ServerProxyObject(DynamicArray *arr) : ProxyBase(boost::interprocess::create_only), arr(arr)
    {
    }

    void ServerProxyObject::run()
    {
        uint8_t command;
        uint64_t recvd;
        uint32_t priority;
        while (active)
        {
            mq->receive(&command, sizeof(int), recvd, priority);
            switch (command)
            {
            case EXIT:
            {
                active = false;
            }
            break;
            case ADD:
            {
                {
                    boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lk(*mutex);
                    arr->addEntry(getValue());
                    setStatus(SUCCESS);
                }
                cond->notify_all();
            }
            break;
            case DELETE:
            {
                {
                    boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lk(*mutex);
                    std::string str = getValue();
                    bool success = arr->deleteEntry(str);
                    setStatus(success ? SUCCESS : ERROR);
                }
                cond->notify_all();
            }
            break;
            case HELP:
            {
                {
                    boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lk(*mutex);
                    boost::format fmt("%d - add(str)\n%d - delete(str)\n%d - get(int)\n%d - exit\n");
                    std::string help = (fmt % ADD % DELETE % GET % EXIT).str();
                    setValue(help);
                }
                cond->notify_all();
            }
            break;
            case GET:
            {
                {
                    boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lk(*mutex);
                    int i = getIndex();
                    try
                    {
                        setValue(arr->getEntry(i));
                        setStatus(SUCCESS);
                    }
                    catch (std::exception &e)
                    {
                        setStatus(ERROR);
                    }
                }
                cond->notify_all();
            }
            }
        }
    }
}
