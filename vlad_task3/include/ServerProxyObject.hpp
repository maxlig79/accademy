#ifndef SERVER_PROXY_OBJECT_H_
#define SERVER_PROXY_OBJECT_H_

#include <ProxyBase.hpp>
#include <DynamicArray.hpp>

namespace server
{
    class ServerProxyObject : public base::ProxyBase
    {
    private:
        bool active;
        DynamicArray *arr;

    public:
        ServerProxyObject(DynamicArray *arr);

    public:
        void run();
    };

}

#endif