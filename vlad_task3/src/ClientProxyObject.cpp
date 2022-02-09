#include <ClientProxyObject.hpp>
#include <Common.hpp>
#include <iostream>
#include <thread>
#include <stdexcept>

using namespace common;

namespace client
{
    ClientProxyObject::ClientProxyObject() : 
    ProxyBase(boost::interprocess::open_only),
    timeout(boost::posix_time::millisec(10))
    {
        id = connect();
        condition = getCondition(id);
    }

    bool ClientProxyObject::addString(const std::string &str)
    {

        boost::interprocess::scoped_lock<boost::interprocess::named_mutex> proc_lk(*proc_mutex);
        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> mem_lk(*mem_mutex);
        setValue(str);
        sendCommand(ADD, mem_lk);
        return getStatus() == SUCCESS;
    }

    bool ClientProxyObject::deleteString(const std::string &str)
    {
        boost::interprocess::scoped_lock<boost::interprocess::named_mutex> proc_lk(*proc_mutex);
        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> mem_lk(*mem_mutex);
        setValue(str);
        sendCommand(DELETE, mem_lk);
        return getStatus() == SUCCESS;
    }

    void ClientProxyObject::exit()
    {
        boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lk(*proc_mutex);
        int code = EXIT;
        if (!getServerAvailable())
        {
            throw std::runtime_error("Server is not available");
        }
        mq->send(&code, sizeof(int), 0);
    }

    std::string ClientProxyObject::get(int index, bool &has_string)
    {
        boost::interprocess::scoped_lock<boost::interprocess::named_mutex> proc_lk(*proc_mutex);
        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> mem_lk(*mem_mutex);
        setIndex(index);
        sendCommand(GET, mem_lk);
        has_string = (getStatus() == SUCCESS);
        if (!has_string)
        {
            return "";
        }
        return getValue();
    }

    int ClientProxyObject::connect()
    {
        boost::interprocess::scoped_lock<boost::interprocess::named_mutex> proc_lk(*proc_mutex);
        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> mem_lk(*mem_mutex);
        int code = ID;
        setId(id);
        mq->send(&code, sizeof(int), 0);
        id_cond->wait(mem_lk);
        if (!getServerAvailable())
        {
            throw std::runtime_error("Server is not available");
        }
        int clientId = getId();
        return clientId;
    }

    int ClientProxyObject::getClientId()
    {
        return id;
    }

    void ClientProxyObject::printHelp()
    {
        boost::interprocess::scoped_lock<boost::interprocess::named_mutex> proc_lk(*proc_mutex);
        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> mem_lk(*mem_mutex);
        sendCommand(HELP, mem_lk);
        std::cout << getValue();
    }

    bool ClientProxyObject::getServerAvailable()
    {
        std::pair<bool *, unsigned long> p = shm->find<bool>(_SERVER_AVAILABLE.c_str());
        return *p.first;
    }

    void ClientProxyObject::sendCommand(Command command, boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> &lk)
    {
        int code = command;
        setId(id);
        mq->send(&code, sizeof(int), 0);
        if (!getServerAvailable())
        {
            throw std::runtime_error("Server is not available");
        }
        condition->wait(lk);   
    }
}
