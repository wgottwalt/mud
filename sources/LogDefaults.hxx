#pragma once

#include <string>

namespace Mud::Log
{
    static const char LogPath[] = "/tmp/mud";
    static const char LogInfo[] = "mud_info.log";
    static const char LogWarn[] = "mud_warn.log";
    static const char LogError[] = "mud_error.log";
    static const char LogFatal[] = "mud_fatal.log";
    static const char LogDebug[] = "mud_debug.log";

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
