#include <ClientProxyObject.hpp>
#include <Common.hpp>
#include <iostream>
#include <thread>

using namespace common;

namespace client
{
    ClientProxyObject::ClientProxyObject(): ProxyBase(boost::interprocess::open_only)
    {
    }

    bool ClientProxyObject::addString(const std::string &str)
    {
        std::scoped_lock<std::mutex> th_lk(thread_mutex);
        boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lk(*mutex);
        setValue(str);
        int code = ADD;
        mq->send(&code, sizeof(int), 0);
        cond->wait(lk);
        return getStatus() == SUCCESS;
    }

    bool ClientProxyObject::deleteString(const std::string &str)
    {
        std::scoped_lock<std::mutex> th_lk(thread_mutex);
        boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lk(*mutex);
        setValue(str);
        int code = DELETE;
        mq->send(&code, sizeof(int), 0);
        cond->wait(lk);
        return getStatus() == SUCCESS;
    }

    void ClientProxyObject::exit()
    {
        std::scoped_lock<std::mutex> th_lk(thread_mutex);
        int code = EXIT;
        mq->send(&code, sizeof(int), 0);
    }

    std::string ClientProxyObject::get(int index, bool &has_string)
    {
        std::scoped_lock<std::mutex> th_lk(thread_mutex);
        boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lk(*mutex);
        setIndex(index);
        int code = GET;
        mq->send(&code, sizeof(int), 0);
        cond->wait(lk);
        Status status = getStatus();
        std::cout << "status is " << status << std::endl;
        has_string = (getStatus() == SUCCESS);
        if (!has_string)
        {
            return "";
        }
        return getValue();
    }

    void ClientProxyObject::printHelp()
    {
        std::scoped_lock<std::mutex> th_lk(thread_mutex);
        boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lk(*mutex);
        int code = HELP;
        mq->send(&code, sizeof(int), 0);
        cond->wait(lk);
        std::cout << getValue();
    }
}
