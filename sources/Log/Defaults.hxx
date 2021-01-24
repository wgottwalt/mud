#pragma once

#include "Support/Time.hxx"

namespace Mud::Log
{
    static const std::string DefaultPath("/tmp/mud");
    static const std::string DefaultInfo("mud_info.log");
    static const std::string DefaultWarn("mud_warn.log");
    static const std::string DefaultError("mud_error.log");
    static const std::string DefaultFatal("mud_fatal.log");
    static const std::string DefaultDebug("mud_debug.log");

    enum class Level {
        Info,
        Warn,
        Error,
        Fatal,
        Debug
    };

    struct Entry {
        const Level level;
        const Support::Time::Timepoint stamp;
        const std::string component;
        const std::string message;
    };

    template <Support::Concepts::Enum T>
    constexpr std::string levelToString(const T level) noexcept
    {
        switch (level)
        {
            case Level::Info:
                return "info";

            case Level::Warn:
                return "warn";

            case Level::Error:
                return "error";

            case Level::Fatal:
                return "fatal";

            case Level::Debug:
            default:
                return "debug";
        }
    }

    template <Support::Concepts::Enum T>
    constexpr T stringToLevel(const std::string &str) noexcept
    {
        if (str == "info")
            return Level::Info;

        if (str == "warn")
            return Level::Warn;

        if (str == "error")
            return Level::Error;

        if (str == "fatal")
            return Level::Fatal;

        return Level::Debug;
    }
}
