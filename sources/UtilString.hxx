#pragma once

#include <string>

namespace Mud::Util
{
    std::string trim(const std::string &data, const char delim, const bool at_start = true,
                     const bool at_end = true);
    std::string trim(const std::string &data, const bool at_start = true, const bool at_end = true);
}
