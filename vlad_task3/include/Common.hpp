#pragma once

#include <string>
#include <cstdint>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>

namespace common
{
    enum Command
    {
        ADD = 1,
        DELETE = 2,
        GET = 3,
        EXIT = 4,
        HELP = 5
    };

    enum Status
    {
        SUCCESS = 0,
        ERROR = 7
    };

    const std::string RESULT = "CAT_RESULT";
    const std::string VALUE = "CAT_VAL";
    const std::string INDEX = "CAT_IDX";
    const std::string _SHM = "CAT_MSHM";
    const std::string _MQ = "CAT_MQ";
    const std::string _COND = "CAT_COND";
    const std::string _MUTEX = "CAT_MUTEX";
}
typedef boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager> StringAllocator;
typedef boost::interprocess::basic_string<char, std::char_traits<char>, StringAllocator> ShmString;
