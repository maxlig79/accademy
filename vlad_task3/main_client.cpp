#include <iostream>
#include <ClientProxyObject.hpp>
#include <Common.hpp>
#include <thread>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <EnumCast.hpp>

using namespace common;

int main()
{
    client::ClientProxyObject obj;
    int code;
    do
    {
        obj.printHelp();
        std::cout << "Enter command: ";
        std::string command;
        std::cin >> command;
        EnumCast<Command> command_cast = EnumCast<Command>(Command::ADD, "add")(Command::GET, "get")(Command::DELETE, "delete")(Command::EXIT, "exit");
        code = (int)(command_cast(command));
        switch (code)
        {
        case GET:
        {
            int i;
            std::cout << "Enter index: ";
            std::cin >> i;
            bool res;
            std::string str = obj.get(i, res);
            if (res)
            {
                std::cout << "arr[" << i << "]="
                          << "\"" << str << "\"" << std::endl;
            }
            else
            {
                std::cout << "Could not get string" << std::endl;
            }
        }
        break;
        case DELETE:
        {
            std::string str;
            std::cout << "Enter string: ";
            std::cin.get();
            std::getline(std::cin, str);
            bool res = obj.deleteString(str);
            if (res)
            {
                std::cout << "String deleted successfully" << std::endl;
            }
            else
            {
                std::cout << "Could not delete string" << std::endl;
            }
        }
        break;
        case ADD:
        {
            std::string str;
            std::cout << "Enter string: ";
            std::cin.get();
            std::getline(std::cin, str);
            bool res = obj.addString(str);
            if (res)
            {
                std::cout << "String added successfully" << std::endl;
            }
            else
            {
                std::cout << "Could not add string" << std::endl;
            }
        }
        break;
        case EXIT:
        {
            obj.exit();
        }
        break;
        }
        std::cout << std::endl;

    } while (code != common::EXIT);

    return 0;
}