#pragma once

#include <string>

namespace Mud::Session
{
    namespace Ansi
    {
                const std::string BMagenta("\x1b[105m");
                const std::string BCyan("\x1b[106m");
                const std::string BWhite("\x1b[107m");
    }

    namespace Telnet
    {
        const std::string NL("\r\n");
        const std::string EOFF("\xFF\xFB\x01");
        const std::string EON("\xFF\xFC\x01");
    }
}
