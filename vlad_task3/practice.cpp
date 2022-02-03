#include <iostream>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>

namespace ipc = boost::interprocess;

struct MyStruct
{
    int m1;
    size_t m2;
    MyStruct(int a, size_t b): m1(a), m2(b) {}
    ~MyStruct()
    {
        std::cout << "Destructor called" << std::endl;
    }
};

typedef ipc::allocator<char, ipc::managed_shared_memory::segment_manager> StringAllocator;
typedef ipc::basic_string<char, std::char_traits<char>, StringAllocator> ShmString;

int main()
{
    ipc::shared_memory_object::remove("ManagedSharedMemory");
    ipc::managed_shared_memory managed_shm(ipc::open_or_create, "ManagedSharedMemory", 1024);
    ShmString *str = managed_shm.find_or_construct<ShmString>("String")("New ", managed_shm.get_segment_manager());
    const char *cstr = (*str).c_str();
    str->insert(3, " string");
    std::cout << *str << std::endl;
    std::cout << cstr << std::endl;

    return 0;

}
/* #include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <iostream>

using namespace boost::interprocess;

int main()
{
  shared_memory_object::remove("Boost");
  managed_shared_memory managed_shm{open_or_create, "Boost", 1024};
  typedef allocator<char,
    managed_shared_memory::segment_manager> CharAllocator;
  typedef basic_string<char, std::char_traits<char>, CharAllocator> string;
  string *s = managed_shm.find_or_construct<string>("String")("Hello!",
    managed_shm.get_segment_manager());
  s->insert(4, ", world");
  std::cout << *s << '\n';
} */