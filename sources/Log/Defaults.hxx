#pragma once

#include <string>

namespace Mud::Log
{
    static const char DefaultPath[] = "/tmp/mud";
    static const char DefaultInfo[] = "mud_info.log";
    static const char DefaultWarn[] = "mud_warn.log";
    static const char DefaultError[] = "mud_error.log";
    static const char DefaultFatal[] = "mud_fatal.log";
    static const char DefaultDebug[] = "mud_debug.log";

    enum class Type : int8_t {
        Info,
        Warn,
        Error,
        Fatal,
        Debug
    };

    std::string logToString(const Type type);
    Type stringToLog(const std::string &str);
}
