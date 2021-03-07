#pragma once

#include <string>
#include "Casts.hxx"

namespace Mud::Support::Ansi
{
    enum class Control : uint8_t {
        Init = 0x1B,
        Escape = 0x5B,
        End = 0x6D
    };

    enum class Font : uint8_t {
        Reset = 0,
        Bold = 1,
        Faint = 2,
        Italic = 3,
        Underline = 4,
        SlowBlink = 5,
        RapidBlink = 6
    };

    namespace Color
    {
        enum class Foreground : uint8_t {
            Black = 30,
            Red = 31,
            Green = 32,
            Yellow = 33,
            Blue = 34,
            Magenta = 35,
            Cyan = 36,
            White = 37,
            BBlack = 90,
            BRed = 91,
            BGreen = 92,
            BYellow = 93,
            BBlue = 94,
            BMagenta = 95,
            BCyan = 96,
            BWhite = 97
        };

        enum class Background : uint8_t {
            Black = 40,
            Red = 41,
            Green = 42,
            Yellow = 43,
            Blue = 44,
            Magenta = 45,
            Cyan = 46,
            White = 47,
            BBlack = 100,
            BRed = 101,
            BGreen = 102,
            BYellow = 103,
            BBlue = 104,
            BMagenta = 105,
            BCyan = 106,
            BWhite = 107
        };
    }

    template <typename T>
    concept AnsiEnum = std::is_enum_v<T> && (std::is_same_v<T,Control> || std::is_same_v<T,Font> ||
                       std::is_same_v<T,Color::Foreground> || std::is_same_v<T,Color::Background>);

    template <AnsiEnum Head, AnsiEnum... Tail>
    std::string sequence(const Head head, Tail &&...tail)
    {
        std::string result{enum_cast(Control::Init), enum_cast(Control::Escape)};

        result += std::to_string(enum_cast(head));
        result += enum_cast(Control::End);

        if constexpr (sizeof... (Tail))
            result += sequence(std::forward<Tail...>(tail...));

        return result;
    }
}
