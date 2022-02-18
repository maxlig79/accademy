#include <iostream>
#include <ClientProxyObject.hpp>
#include <Common.hpp>
#include <thread>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <EnumCast.hpp>
#include <cstring>

using namespace common;

int main(int argc, char **argv)
{
    client::ClientProxyObject obj;
    int code;
    bool prompt = (argc < 2) || strcmp(argv[1], "--no-prompt");
    do
    {
        if (prompt)
        {
            obj.printHelp();
            std::cout << "Enter command: ";
        }
        std::string command;
        std::cin >> command;
        EnumCast<Command> command_cast =
            EnumCast<Command>(Command::ADD, "add")(Command::GET, "get")(Command::DELETE, "delete")(Command::EXIT, "exit");
        try
        {
        code = (int)(command_cast(command));
        }
        catch(std::exception &e)
        {
            code = (int)common::EXIT;
        }
        switch (code)
        {
        case GET:
        {
            int i;
            if (prompt)
            {
                std::cout << "Enter index: ";
            }
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
            if (prompt)
            {
                std::cout << "Enter string: ";
            }
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
            if (prompt)
            {
                std::cout << "Enter string: ";
            }
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
        break;
        }
        if (prompt)
        {
            std::cout << std::endl;
        }

    } while (code != common::EXIT);

    return 0;
}