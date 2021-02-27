#include "String.hxx"

using namespace Mud::Support::String;

namespace Impl
{
    std::string __trim(std::string &&str, const char delim, const bool at_start, const bool at_end)
    {
        if (at_start)
            while (!str.empty() && (*(str.begin())) == delim)
                str.erase(str.begin(), str.begin() + 1);
        if (at_end)
            while (!str.empty() && (*(str.end() - 1)) == delim)
                str.erase(str.end() - 1, str.end());

        return str;
    }

    std::string __trim(std::string &&str, const bool at_start, const bool at_end)
    {
        if (at_start)
            while (!str.empty() && std::isspace(*(str.begin())))
                str.erase(str.begin(), str.begin() + 1);
        if (at_end)
            while (!str.empty() && std::isspace(*(str.end() - 1)))
                str.erase(str.end() - 1, str.end());

        return str;
    }
}

void trim(std::string &str, const char delim, const bool at_start, const bool at_end)
{
    Impl::__trim(std::forward<std::string>(str), delim, at_start, at_end);
}

std::string trim(const std::string &str, const char delim, const bool at_start, const bool at_end)
{
    std::string tmp(str);

    return Impl::__trim(std::forward<std::string>(tmp), delim, at_start, at_end);
}

std::string trim(std::string &&str, const char delim, const bool at_start, const bool at_end)
{
    return Impl::__trim(std::forward<std::string>(str), delim, at_start, at_end);
}

void trim(std::string &str, const bool at_start, const bool at_end)
{
    Impl::__trim(std::forward<std::string>(str), at_start, at_end);
}

std::string trim(const std::string &str, const bool at_start, const bool at_end)
{
    std::string tmp(str);

    return Impl::__trim(std::forward<std::string>(tmp), at_start, at_end);
}

std::string trim(std::string &&str, const bool at_start, const bool at_end)
{
    return Impl::__trim(std::forward<std::string>(str), at_start, at_end);
}
