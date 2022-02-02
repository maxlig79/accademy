#include <common.h>
#include <base_class.hpp>

void start(std::unique_ptr<Server_Client_Base>);

int main()
{
   std::unique_ptr<Client> client = std::make_unique<Client>();
   start(std::move(client));
   return 0;
}