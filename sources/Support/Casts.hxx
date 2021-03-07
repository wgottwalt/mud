#pragma once

#include "Concepts.hxx"

template <Mud::Support::Concepts::Enum E>
constexpr std::underlying_type_t<E> enum_cast(const E val) noexcept
{
    return static_cast<std::underlying_type_t<E>>(val);
}
