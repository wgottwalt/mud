#pragma once

#include <chrono>
#include <concepts>
#include <tuple>
#include <type_traits>

namespace ext
{
    template <typename>
    struct __is_function_pointer_helper
    : public std::false_type { };

    template<typename _Tp>
    struct __is_function_pointer_helper<_Tp *>
    : public std::__or_<std::is_pointer<_Tp>,
                        std::is_function<std::remove_pointer_t<_Tp>>> { };

    template <typename _Tp>
    struct is_function_pointer
    : public __is_function_pointer_helper<std::__remove_cv_t<_Tp>>::type { };

    template <typename _Tp>
    inline constexpr bool is_function_pointer_v = is_function_pointer<_Tp>::value;
}

namespace Mud::Support::Concepts
{
    template <typename T>
    concept Integer = std::is_integral_v<T>;

    template <typename T>
    concept SignedInteger = std::is_integral_v<T> && std::is_signed_v<T>;

    template <typename T>
    concept UnsignedInteger = std::is_integral_v<T> && std::is_unsigned_v<T>;

    template <typename T>
    concept Float = std::is_floating_point_v<T>;

    template <typename T>
    concept Number = std::is_integral_v<T> || std::is_floating_point_v<T>;

    template <typename T>
    concept Enum = std::is_enum_v<T>;

    template <typename T>
    concept Class = std::is_class_v<T>;

    template <typename T>
    concept FunctionPointer = ext::is_function_pointer_v<T> || std::is_member_function_pointer_v<T>;

    template <typename T, size_t MinSize = 1, size_t MaxSize = std::numeric_limits<size_t>::max()>
    concept Tuple = requires (T val){ {std::get<0>(val)}; } &&
                    ((std::tuple_size_v<std::remove_cvref_t<T>> - MinSize) <= (MaxSize - MinSize));

    template <typename T>
    concept Clock = std::is_same_v<T,std::chrono::system_clock> ||
                    std::is_same_v<T,std::chrono::steady_clock> ||
                    std::is_same_v<T,std::chrono::high_resolution_clock>;
}
