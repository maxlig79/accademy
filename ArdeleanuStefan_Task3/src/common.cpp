#include <common.h>
#include <base_class.hpp>

const CommandPair split_command(const std::string &command)
{
    // BONUS TASK: Make this function (much) better!

    CommandPair out;
    if ((command == HELP_COMMAND) || (command == EXIT_COMMAND))
    {
        const auto commandID = COMMAND_TO_ID.find(command);
        out.first = commandID->second;
        out.second = ""; // empty string, we don't care about it in this case
    }
    else
    {
        std::vector<std::string> strs;
        // this will not work if there are multiple ';' chars in the input, but it is good enough for now.
        boost::split(strs, command, boost::is_any_of(";"));

        if (strs.size() != 2)
            throw std::out_of_range("Expected 'command;value' pair");

        const auto commandID = COMMAND_TO_ID.find(strs[0]);
        if (commandID == COMMAND_TO_ID.end())
        {
            throw std::invalid_argument("received command does not exist");
        }

        out.first = commandID->second;
        out.second = strs[1];
    }

    return out;
}

void start(std::unique_ptr<Server_Client_Base> base)
{
    const std::type_info &ptypeinfo = typeid(*base);
    MessageQueueRequest msg;
    unsigned int priority;
    boost::interprocess::message_queue::size_type recvd_size;
    auto IPC_mutex = base->getSharedMemory()->find_or_construct<boost::interprocess::interprocess_mutex>(IPC_MUTEX.c_str())();
    auto IPC_cond_var = base->getSharedMemory()->find_or_construct<boost::interprocess::interprocess_condition>(IPC_CONDITIONAL_VAR.c_str())();

    while ((strcmp(msg.command, EXIT_COMMAND.c_str()) != 0))
    {
        if (ptypeinfo == typeid(Client))
        {
            std::cin >> msg.command;
            base->getMessageQueue()->send(&msg, sizeof(msg), 0);
        }
        if (ptypeinfo == typeid(Server))
        {
            base->getMessageQueue()->receive(&msg, sizeof(msg), recvd_size, priority);
        }
        CommandPair command_pair = split_command(msg.command);
        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(*IPC_mutex);
        if (ptypeinfo == typeid(Client))
        {
            IPC_cond_var->wait(lock);
        }

        switch (command_pair.first)
        {

        case CommandIds::HELP:
        {
            if (ptypeinfo == typeid(Client))
            {
                std::pair<Shared::Vector *, size_t> vec = base->getSharedMemory()->find<Shared::Vector>(HELP_COMMAND.c_str());

                for (int i = 0; i < vec.first->size(); i = i + 2)
                {
                    std::cout << vec.first->at(i) << " " << vec.first->at(i + 1) << std::endl;
                }

                base->getSharedMemory()->destroy<Shared::Vector>(HELP_COMMAND.c_str());
            }
            else if (ptypeinfo == typeid(Server))
            {
                Shared::Vector *vec = base->getSharedMemory()->find_or_construct<Shared::Vector>(HELP_COMMAND.c_str())(base->getSharedMemory()->get_allocator<Shared::StringAllocator>());

                for (auto &cmd : COMMAND_TO_HELP)
                {
                    vec->push_back(Shared::String(cmd.first.begin(), cmd.first.end(), base->getSharedMemory()->get_segment_manager()));
                    vec->push_back(Shared::String(cmd.second.begin(), cmd.second.end(), base->getSharedMemory()->get_segment_manager()));
                }
            }
            break;
        }

        case CommandIds::EXIT:
        {
            boost::interprocess::message_queue::remove(MESSAGE_QUEUE_NAME.c_str());
            boost::interprocess::shared_memory_object::remove(SHARED_MEMORY_NAME.c_str());

            break;
        }

        case CommandIds::ADD:
        {
            if (ptypeinfo == typeid(Client))
            {
                std::pair<Shared::String *, size_t> p = base->getSharedMemory()->find<Shared::String>(ADD_COMMAND.c_str());
                std::cout << p.first->c_str() << std::endl;
                base->getSharedMemory()->destroy<Shared::String>(ADD_COMMAND.c_str());
            }
            else if (ptypeinfo == typeid(Server))
            {
                base->setStringArrayEntry(command_pair.second);
                base->getSharedMemory()->find_or_construct<Shared::String>(ADD_COMMAND.c_str())("Add OK", base->getSharedMemory()->get_segment_manager());
            }
            break;
        }

        case CommandIds::DELETE:
        {
            if (ptypeinfo == typeid(Client))
            {
                std::pair<Shared::String *, size_t> p = base->getSharedMemory()->find<Shared::String>(DELETE_COMMAND.c_str());
                std::cout << p.first->c_str() << std::endl;

                base->getSharedMemory()->destroy<Shared::String>(DELETE_COMMAND.c_str());
            }
            else if (ptypeinfo == typeid(Server))
            {
                if (base->deleteStringArray(command_pair.second))
                {
                    base->getSharedMemory()->construct<Shared::String>(DELETE_COMMAND.c_str())("DELETE OK", base->getSharedMemory()->get_segment_manager());
                }
                else
                {
                    base->getSharedMemory()->construct<Shared::String>(DELETE_COMMAND.c_str())("DELETE NOT OK", base->getSharedMemory()->get_segment_manager());
                }
            }
            break;
        }

        case CommandIds::GET:
        {
            if (ptypeinfo == typeid(Client))
            {
                std::pair<Shared::String *, size_t> p = base->getSharedMemory()->find<Shared::String>(GET_COMMAND.c_str());
                std::cout << p.first->c_str() << std::endl;

                base->getSharedMemory()->destroy<Shared::String>(GET_COMMAND.c_str());
            }
            else if (ptypeinfo == typeid(Server))
            {
                if (base->getStringArrayEntry(std::stoi(command_pair.second)))
                {
                    base->getSharedMemory()->construct<Shared::String>(GET_COMMAND.c_str())((*base->getStringArrayEntry(std::stoi(command_pair.second))).c_str(), base->getSharedMemory()->get_segment_manager());
                }
                else
                {
                    base->getSharedMemory()->construct<Shared::String>(GET_COMMAND.c_str())("NOT FOUND", base->getSharedMemory()->get_segment_manager());
                }
            }
            break;
        }

        default:
        {
            break;
        }
        }
        if (ptypeinfo == typeid(Server))
            IPC_cond_var->notify_one();
    }
}