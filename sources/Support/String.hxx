#pragma once

#include <sstream>
#include <string>

namespace Mud::Support::String
{
    namespace Impl
    {
        using TestFunc = int32_t(*)(int32_t);
    }

    template <typename H, typename... T>
    std::string str(const H &head, const T &...tail)
    {
        std::stringstream strm;

        if constexpr (sizeof... (T))
            strm << head << str(tail...);
        else
            strm << head;

        return strm.str();
    }

    std::string trim(const std::string &str, const bool at_begin = true, const bool at_end = true);
    std::string trim(std::string &&str, const bool at_begin = true, const bool at_end = true);
    std::string trim(const std::string &str, const char delim, const bool at_begin = true,
                     const bool at_end = true);
    std::string trim(std::string &&str, const char delim, const bool at_begin = true,
                     const bool at_end = true);
    std::string trim(const std::string &str, Impl::TestFunc cb, const bool at_begin = true,
                     const bool at_end = true, const bool neg = true);
    std::string trim(std::string &&str, Impl::TestFunc cb, const bool at_begin = true,
                     const bool at_end = true, const bool neg = true);
}
