#ifndef CLIENT_PROXY_OBJECT_H_
#define CLIENT_PROXY_OBJECT_H_

#include <string>
#include <ProxyBase.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

namespace client
{
    class ClientProxyObject : public base::ProxyBase
    {
    private:
        int id;

    private:
        int connect();
        bool getServerAvailable();
        void sendCommand(common::Command command, boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> &lk);

    public:
        ClientProxyObject();
        bool addString(const std::string &str);
        bool deleteString(const std::string &str);
        std::string get(int index, bool &has_string);
        void exit();
        void printHelp();
    };
}

#endif