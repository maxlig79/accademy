#ifndef SERVER_PROXY_OBJECT_H_
#define SERVER_PROXY_OBJECT_H_

#include <ProxyBase.hpp>
#include <DynamicArray.hpp>
#include <atomic>

namespace server
{
    class ServerProxyObject : public base::ProxyBase
    {
    private:
        std::atomic_bool active;
        std::map<int, DynamicArray> arrs;
        int max_clients;
        

    public:
        ServerProxyObject(int max_clients);
        ~ServerProxyObject();
        
    public:
        void run();
        void stop();

    private:
        void setServerAvailable(bool value);
    };

}

#endif