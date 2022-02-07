#pragma once

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <cstring>
#include <stddef.h>
#include <string>
#include <vector>
#include <utility>
#include <boost/algorithm/string.hpp>
#include <map>
#include "DynamicStringArray.hpp"

using namespace boost::interprocess;

typedef allocator <char, managed_shared_memory::segment_manager> CharAllocator;
typedef basic_string <char, std::char_traits<char>, CharAllocator> MyStringAllocator;
typedef allocator <MyStringAllocator, managed_shared_memory::segment_manager> StringAllocator;
typedef vector <MyStringAllocator, StringAllocator> MyVectorAllocator;

constexpr size_t MAX_COMMAND_LENGTH = 100;

struct MessageQueueRequest
{
    char command[MAX_COMMAND_LENGTH]{};
};

const std::string MUTEX_IPC("academy_ipc_task_Mutex");

const std::string CONDITION_IPC("academy_ipc_task_Condition");

const std::string MESSAGE_QUEUE_NAME("academy_ipc_task_mq");

const std::string SHARED_MEMORY_NAME("academy_ipc_task_sm");

constexpr size_t SHARED_MEMORY_SIZE = 2048;

constexpr int MAX_MESSAGE_NUMBER = 100;

constexpr size_t MAX_MESSAGE_SIZE = sizeof(MessageQueueRequest);

const std::string HELP_COMMAND("help");

const std::string EXIT_COMMAND("exit");

const std::string ADD_COMMAND("add");

const std::string DELETE_COMMAND("delete");

const std::string GET_COMMAND("get");

const std::map<const std::string, const std::string> COMMAND_TO_HELP{
        std::make_pair(HELP_COMMAND, "Print help"), 
        std::make_pair(EXIT_COMMAND, "Exit application"), 
        std::make_pair(ADD_COMMAND, "Add new element to DynamicStringList"), 
        std::make_pair(DELETE_COMMAND, "Delete element from DynamicStringList"), 
        std::make_pair(GET_COMMAND, "Get element from DynamicStringList")
    };

enum class CommandIds : int
{
    HELP,
    EXIT,
    ADD,
    DELETE,
    GET
};

const std::map<const std::string, const CommandIds> COMMAND_TO_ID{
        std::make_pair(HELP_COMMAND, CommandIds::HELP), 
        std::make_pair(EXIT_COMMAND, CommandIds::EXIT), 
        std::make_pair(ADD_COMMAND, CommandIds::ADD), 
        std::make_pair(DELETE_COMMAND, CommandIds::DELETE), 
        std::make_pair(GET_COMMAND, CommandIds::GET)
};

using CommandPair = std::pair<CommandIds, std::string>;
const CommandPair split_command(const std::string &command)
{
    // BONUS TASK: Make this function (much) better!

    CommandPair out;
    if ((command == HELP_COMMAND) || (command == EXIT_COMMAND) )
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
