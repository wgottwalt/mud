#pragma once

#include "Concepts.hxx"

namespace Mud::Support::Endian
{
    namespace Impl
    {
        template <typename T>
        concept EndianNumber = requires (T){ (sizeof (T) >= 8) && (sizeof (T) <= 64); } &&
                                        std::is_integral_v<T> || std::is_floating_point_v<T>;
    }

    enum class Order : int32_t {
        Little = __ORDER_LITTLE_ENDIAN__,
        Big = __ORDER_BIG_ENDIAN__,
        Native = __BYTE_ORDER__
    };

    template <Impl::EndianNumber T>
    constexpr inline T swap(const T val) noexcept
    {
        if constexpr (sizeof (T) == sizeof (uint16_t))
            return ((val & 0x00FF) << 8) | ((val & 0xFF00) >> 8);
        else if constexpr (sizeof (T) == sizeof (uint32_t))
            return ((val & 0x000000FF) << 24) | ((val & 0x0000FF00) << 8) |
                   ((val & 0x00FF0000) >> 8) | ((val & 0xFF000000) >> 24);
        else if constexpr (sizeof (T) == sizeof (uint64_t))
            return ((val & 0x00000000000000FFull) << 56) | ((val & 0x000000000000FF00ull) << 40) |
                   ((val & 0x0000000000FF0000ull) << 24) | ((val & 0x00000000FF000000ull) << 8) |
                   ((val & 0x000000FF00000000ull) >> 8) | ((val & 0x0000FF0000000000ull) >> 24) |
                   ((val & 0x00FF000000000000ull) >> 40) | ((val & 0xFF00000000000000ull) >> 56);

        return val;
    }

    template <Impl::EndianNumber T>
    constexpr inline T toBE(const T val) noexcept
    {
        if constexpr (Order::Native == Order::Little)
            return swap(val);
        else
            return val;
    }

    template <Impl::EndianNumber T>
    constexpr inline T fromBE(const T val) noexcept
    {
        if constexpr (Order::Native == Order::Little)
            return swap(val);
        else
            return val;
    }

    template <Impl::EndianNumber T>
    constexpr inline T toLE(const T val) noexcept
    {
        if constexpr (Order::Native == Order::Little)
            return val;
        else
            return swap(val);
    }

    template <Impl::EndianNumber T>
    constexpr inline T fromLE(const T val) noexcept
    {
        if constexpr (Order::Native == Order::Little)
            return val;
        else
            return swap(val);
    }
}
