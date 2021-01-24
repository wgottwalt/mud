#pragma once

#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
#include "Concepts.hxx"

// XXX: Some of the convertion functions can not be instantiated, because some of the clock types
//      provided by the c++ lib are just missing essential parts. std::chrono::system_clock is the
//      most safe bet, but may lack precission on non-Linux systems. Though this code is never
//      ment to run on something else than Linux, well a BSD may be just fine (if you find a BSD
//      with a C++20 compiler).

namespace Mud::Support::Time
{
    using Clock = std::chrono::system_clock;
    using Rep = Clock::rep;
    using Period = Clock::period;
    using Duration = Clock::duration;
    using Timepoint = Clock::time_point;

    // fromat: YYYYMMDD.hhmmss - 24h
    static const std::string DefaultCompactDateTime = "%Y%m%j.%H%M%S";
    static const std::string DefaultDateTime = "%Y/%m/%j %H:%M:%S";

    template <Concepts::Clock T = Clock>
    constexpr Timepoint now() noexcept
    {
        return T::now();
    }

    template <Concepts::Clock T = Clock>
    constexpr time_t nowTimeT() noexcept
    {
        return toTimeT<T>(now<T>());
    }

    template <Concepts::Clock T = Clock>
    constexpr time_t toTimeT(const Timepoint &timepoint) noexcept
    {
        return T::to_time_t(timepoint);
    }

    template <Concepts::Clock T = Clock>
    constexpr Timepoint toTimepoint(const time_t timet) noexcept
    {
        return T::from_time_t(timet);
    }

    template <Concepts::Clock T = Clock>
    constexpr std::string toDateString(const time_t timet,
                                       const std::string &format = DefaultCompactDateTime)
    {
        const struct std::tm temp = *std::localtime(&timet);
        std::stringstream result;

        result << std::put_time(&temp, format.c_str());

        return result.str();
    }

    template <Concepts::Clock T = Clock>
    constexpr std::string toDateString(const typename T::time_point &timepoint,
                                       const std::string &format = DefaultCompactDateTime)
    {
        return toDateString(toTimeT(timepoint), format);
    }

    template <Concepts::Clock T = Clock>
    constexpr size_t ns(const typename T::duration &duration) noexcept
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    }

    template <Concepts::Clock T = Clock>
    constexpr size_t us(const typename T::duration &duration) noexcept
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    }

    template <Concepts::Clock T = Clock>
    constexpr size_t ms(const typename T::duration &duration) noexcept
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }

    template <Concepts::Clock T = Clock>
    constexpr size_t sec(const typename T::duration &duration) noexcept
    {
        return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    }

    template <Concepts::Clock T = Clock>
    constexpr size_t min(const typename T::duration &duration) noexcept
    {
        return std::chrono::duration_cast<std::chrono::minutes>(duration).count();
    }

    template <Concepts::Clock T = Clock>
    constexpr size_t hr(const typename T::duration &duration)
    {
        return std::chrono::duration_cast<std::chrono::hours>(duration).count();
    }
}
