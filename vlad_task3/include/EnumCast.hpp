#ifndef CAT_UTILS_ENUM_CAST_H_
#define CAT_CUBE_UTILS_ENUM_CAST_H_

#include <map>
#include <string>

template <typename T>
class EnumCast
{
private:
    std::map<T, std::string> value_to_string;
    std::map<std::string, T> string_to_value;

public:
    EnumCast(T value, const std::string &name)
    {
        add(name, value);
    }

    EnumCast(const EnumCast &enum_cast)
    {
        value_to_string.clear();
        string_to_value.clear();
        value_to_string = enum_cast.value_to_string;
        string_to_value = enum_cast.string_to_value;
    }

    EnumCast &operator()(const T &value, const std::string &name)
    {
        add(name, value);
        return *this;
    }

    const std::string operator()(T value) const
    {
        return value_to_string.at(value);
    }

    const T operator()(const std::string &name) const
    {
        return string_to_value.at(name);
    }

    void add(const std::string &name, T value)
    {
        value_to_string[value] = name;
        string_to_value[name] = value;
    }
};
#endif