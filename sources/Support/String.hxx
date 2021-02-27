#pragma once

#include <sstream>
#include <string>

namespace Mud::Support::String
{
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

    void trim(std::string &str, const char delim, const bool at_start = true,
              const bool at_end = true);
    std::string trim(const std::string &str, const char delim, const bool at_start = true,
                     const bool at_end = true);
    std::string trim(std::string &&str, const char delim, const bool at_start = true,
                     const bool at_end = true);

    void trim(std::string &str, const bool at_start = true, const bool at_end = true);
    std::string trim(const std::string &str, const bool at_start = true, const bool at_end = true);
    std::string trim(std::string &&str, const bool at_start = true, const bool at_end = true);
}
