#include "String.hxx"

namespace Mud::Support::String
{
    namespace Impl
    {
        std::string __trim(std::string &&str, const bool at_begin, const bool at_end)
        {
            if (at_begin)
                while (!str.empty() && std::isspace(*(str.begin())))
                    str.erase(str.begin(), str.begin() + 1);
            if (at_end)
                while (!str.empty() && std::isspace(*(str.end() - 1)))
                    str.erase(str.end() - 1, str.end());

            return str;
        }

        std::string __trim(std::string &&str, const char delim, const bool at_begin,
                           const bool at_end)
        {
            if (at_begin)
                while (!str.empty() && (*(str.begin())) == delim)
                    str.erase(str.begin(), str.begin() + 1);
            if (at_end)
                while (!str.empty() && (*(str.end() - 1)) == delim)
                    str.erase(str.end() - 1, str.end());

            return str;
        }

        std::string __trim(std::string &&str, Impl::TestFunc cb, const bool at_begin,
                           const bool at_end, const bool neg)
        {
            if (at_begin)
                while (!str.empty() && (neg && cb(*(str.begin()))))
                    str.erase(str.begin(), str.begin() + 1);
            if (at_end)
                while (!str.empty() && (neg && cb(*(str.end() - 1))))
                    str.erase(str.end() - 1, str.end());

            return str;
        }
    }

    std::string trim(const std::string &str, const bool at_begin, const bool at_end)
    {
        std::string tmp(str);

        return Impl::__trim(std::move(tmp), at_begin, at_end);
    }

    std::string trim(std::string &&str, const bool at_begin, const bool at_end)
    {
        return Impl::__trim(std::move(str), at_begin, at_end);
    }

    std::string trim(const std::string &str, const char delim, const bool at_begin,
                     const bool at_end)
    {
        std::string tmp(str);

        return Impl::__trim(std::move(tmp), delim, at_begin, at_end);
    }

    std::string trim(std::string &&str, const char delim, const bool at_begin, const bool at_end)
    {
        return Impl::__trim(std::move(str), delim, at_begin, at_end);
    }

    std::string trim(const std::string &str, Impl::TestFunc cb, const bool at_begin,
                     const bool at_end, const bool neg)
    {
        std::string tmp(str);

        return Impl::__trim(std::move(tmp), cb, at_begin, at_end, neg);
    }

    std::string trim(std::string &&str, Impl::TestFunc cb, const bool at_begin, const bool at_end,
                     const bool neg)
    {
        return Impl::__trim(std::move(str), cb, at_begin, at_end, neg);
    }
}
