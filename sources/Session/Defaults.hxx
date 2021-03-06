#pragma once

#include <string>

namespace Mud::Session::Telnet
{
    const std::string NL("\r\n");
    const std::string EOFF("\xFF\xFB\x01");
    const std::string EON("\xFF\xFC\x01");
}
