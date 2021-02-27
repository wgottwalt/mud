#pragma once

#include <sstream>
#include <string>

namespace Mud::Support::String
{
    namespace Impl
    {
        template <bool Begin, bool End>
        std::string __trim(std::string &&str, const char delim)
        {
            if constexpr (Begin)
                while (!str.empty() && (*(str.begin())) == delim)
                    str.erase(str.begin(), str.begin() + 1);
            if constexpr (End)
                while (!str.empty() && (*(str.end() - 1)) == delim)
                    str.erase(str.end() - 1, str.end());

            return str;
        }

        template <bool Begin, bool End>
        std::string __trim(std::string &&str)
        {
            if constexpr (Begin)
                while (!str.empty() && std::isspace(*(str.begin())))
                    str.erase(str.begin(), str.begin() + 1);
            if constexpr (End)
                while (!str.empty() && std::isspace(*(str.end() - 1)))
                    str.erase(str.end() - 1, str.end());

            return str;
        }
    }

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

    template <bool Begin = true, bool End = true>
    void trim(std::string &str, const char delim)
    {
        Impl::__trim<Begin,End>(std::move(str), delim);
    }

    template <bool Begin = true, bool End = true>
    std::string trim(const std::string &str, const char delim)
    {
        std::string tmp(str);

        return Impl::__trim<Begin,End>(std::move(tmp), delim);
    }

    template <bool Begin = true, bool End = true>
    std::string trim(std::string &&str, const char delim)
    {
        return Impl::__trim<Begin,End>(std::move(str), delim);
    }

    template <bool Begin = true, bool End = true>
    void trim(std::string &str)
    {
        Impl::__trim<Begin,End>(std::move(str));
    }

    template <bool Begin = true, bool End = true>
    std::string trim(const std::string &str)
    {
        std::string tmp(str);

        return Impl::__trim<Begin,End>(std::move(tmp));
    }

    template <bool Begin = true, bool End = true>
    std::string trim(std::string &&str)
    {
        return Impl::__trim<Begin,End>(std::move(str));
    }
}
