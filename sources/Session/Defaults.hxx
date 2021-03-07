#pragma once

#include <string>

namespace Mud::Session
{
    namespace Ansi
    {
        const std::string Reset("\x1b[0m");

        namespace Text
        {
            const std::string Bold("\x1b[1m");
            const std::string Faint("\x1b[2m");
            const std::string Italic("\x1b[3m");
            const std::string Underline("\x1b[4m");
            const std::string SlowBlink("\x1b[5m");
            const std::string RapidBlink("\x1b[6m");
        }

        namespace Color
        {
            namespace FG
            {
                const std::string Black("\x1b[30m");
                const std::string Red("\x1b[31m");
                const std::string Green("\x1b[32m");
                const std::string Yellow("\x1b[33m");
                const std::string Blue("\x1b[34m");
                const std::string Magenta("\x1b[35m");
                const std::string Cyan("\x1b[36m");
                const std::string White("\x1b[37m");

                const std::string BBlack("\x1b[90m");
                const std::string BRed("\x1b[91m");
                const std::string BGreen("\x1b[92m");
                const std::string BYellow("\x1b[93m");
                const std::string BBlue("\x1b[94m");
                const std::string BMagenta("\x1b[95m");
                const std::string BCyan("\x1b[96m");
                const std::string BWhite("\x1b[97m");
            }

            namespace BG
            {
                const std::string Black("\x1b[40m");
                const std::string Red("\x1b[41m");
                const std::string Green("\x1b[42m");
                const std::string Yellow("\x1b[43m");
                const std::string Blue("\x1b[44m");
                const std::string Magenta("\x1b[45m");
                const std::string Cyan("\x1b[46m");
                const std::string White("\x1b[47m");

                const std::string BBlack("\x1b[100m");
                const std::string BRed("\x1b[101m");
                const std::string BGreen("\x1b[102m");
                const std::string BYellow("\x1b[103m");
                const std::string BBlue("\x1b[104m");
                const std::string BMagenta("\x1b[105m");
                const std::string BCyan("\x1b[106m");
                const std::string BWhite("\x1b[107m");
            }
        }
    }

    namespace Telnet
    {
        const std::string NL("\r\n");
        const std::string EOFF("\xFF\xFB\x01");
        const std::string EON("\xFF\xFC\x01");
    }
}
