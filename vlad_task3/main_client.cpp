#include <iostream>
#include <ClientProxyObject.hpp>

int main()
{
    printf("GET=%d\n", common::GET);
    ClientProxyObject obj;
    int code = 0;
    do
    {
        obj.printHelp();
        std::cout << "Enter: ";
        std::cin >> code;
        //Could not use switch because extern constants must be known at compile-time
        //Have to use extern constants because of conflicting declarations
        if (code == common::GET)
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
        if (code == common::ADD)
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
        if (code == common::DELETE)
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
        if (code == common::EXIT)
        {
            obj.exit();
        }

    } while (code != common::EXIT);

    return 0;
}