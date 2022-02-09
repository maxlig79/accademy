#include <iostream>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/format.hpp>
#include <Common.hpp>
#include <DynamicArray.hpp>
#include <ServerProxyObject.hpp>

using namespace common;

int main()
{
    server::ServerProxyObject serv(5);
    serv.run();
    return 0;
}