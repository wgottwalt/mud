#pragma once

#include <sstream>
#include <string>

namespace Mud::Util
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

    std::string trim(const std::string &data, const char delim, const bool at_start = true,
                     const bool at_end = true);
    std::string trim(const std::string &data, const bool at_start = true, const bool at_end = true);
}
