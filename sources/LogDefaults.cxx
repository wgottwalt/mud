#include "LogDefaults.hxx"

using namespace Mud::Log;

std::string logToString(const Type type)
{
    switch (type)
    {
        case Type::Info:
            return "info";

        case Type::Warn:
            return "warn";

        case Type::Error:
            return "error";

        case Type::Fatal:
            return "fatal";

        case Type::Debug:
        default:
            return "debug";
    }
}

Type stringToLog(const std::string &str)
{
    if (str == "info")
        return Type::Info;

    if (str == "warn")
        return Type::Warn;

    if (str == "error")
        return Type::Error;

    if (str == "fatal")
        return Type::Fatal;

    return Type::Debug;
}
