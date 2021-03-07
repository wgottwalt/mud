#include <algorithm>
#include <functional>
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

        std::string __trim(std::string &&str, TestFunc cb, const bool at_begin, const bool at_end,
                           const bool neg)
        {
            if (at_begin)
                while (!str.empty() && (neg && cb(*(str.begin()))))
                    str.erase(str.begin(), str.begin() + 1);
            if (at_end)
                while (!str.empty() && (neg && cb(*(str.end() - 1))))
                    str.erase(str.end() - 1, str.end());

            return str;
        }

        std::string __clean(std::string &&str, const char delim)
        {
            std::remove(str.begin(), str.end(), delim);

            return str;
        }

        std::string __clean(std::string &&str, Impl::TestFunc cb, const bool neg)
        {
            if (neg)
                std::remove_if(str.begin(), str.end(), std::not_fn(cb));
            else
                std::remove_if(str.begin(), str.end(), cb);

            return str;
        }
    }

    //--- trim functions ---

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

    //--- removal functions ---

    std::string clean(const std::string &str, const char delim)
    {
        std::string tmp(str);

        return Impl::__clean(std::move(tmp), delim);
    }

    std::string clean(std::string &&str, const char delim)
    {
        return Impl::__clean(std::move(str), delim);
    }

    std::string clean(const std::string &str, Impl::TestFunc cb, const bool neg)
    {
        std::string tmp(str);

        return Impl::__clean(std::move(tmp), cb, neg);
    }

    std::string clean(std::string &&str, Impl::TestFunc cb, const bool neg)
    {
        return Impl::__clean(std::move(str), cb, neg);
    }
}
