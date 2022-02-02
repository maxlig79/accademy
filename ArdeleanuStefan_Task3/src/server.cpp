#include <common.h>
#include <base_class.hpp>

void start(std::unique_ptr<Server_Client_Base>);

int main()
{
   std::unique_ptr<Server> server = std::make_unique<Server>();
   start(std::move(server));
   return 0;
}