#ifndef CLIENT_PROXY_OBJECT_H_
#define CLIENT_PROXY_OBJECT_H_

#include <string>
#include <Common.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <memory>

class ClientProxyObject
{
public:
    bool addString(const std::string &str);
    bool deleteString(const std::string &str);
    std::string get(int index, bool &has_string);
    void exit();
    void printHelp();
    ClientProxyObject();

private:
    boost::interprocess::message_queue mq;
    boost::interprocess::managed_shared_memory shm;
    boost::interprocess::named_condition cond;
    boost::interprocess::named_mutex mutex;
    

private:
    void setValue(const std::string &value);
    void setIndex(int value);
    std::string getValue();
    bool success();
};

#endif