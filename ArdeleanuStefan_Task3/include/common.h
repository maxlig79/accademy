#pragma once

#include <stddef.h>
#include <vector>
#include <string>
#include <utility>
#include <boost/algorithm/string.hpp>
#include <map>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <iostream>
#include <memory>
#include <boost/asio.hpp>

namespace Shared
{
   using Segment = boost::interprocess::managed_shared_memory;
   using Manager = Segment::segment_manager;

   using CharAllocator = boost::interprocess::allocator<char, Manager>;
   using String = boost::interprocess::basic_string<char, std::char_traits<char>, CharAllocator>;

   using StringAllocator = boost::interprocess::allocator<String, Manager>;
   using Vector = boost::interprocess::vector<String, StringAllocator>;
}

constexpr size_t MAX_COMMAND_LENGTH = 100;

struct MessageQueueRequest
{
    char command[MAX_COMMAND_LENGTH]{};
};

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

const std::string IPC_MUTEX("ipc_mutex");
const std::string IPC_CONDITIONAL_VAR("ipc_cond_var");

const std::map<const std::string, const std::string> COMMAND_TO_HELP{
    std::make_pair(HELP_COMMAND, "Print help"),
    std::make_pair(EXIT_COMMAND, "Exit application"),
    std::make_pair(ADD_COMMAND, "Add new element to DynamicStringList"),
    std::make_pair(DELETE_COMMAND, "Delete element from DynamicStringList"),
    std::make_pair(GET_COMMAND, "Get element from DynamicStringList")};

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
    std::make_pair(GET_COMMAND, CommandIds::GET)};

using CommandPair = std::pair<CommandIds, std::string>;
