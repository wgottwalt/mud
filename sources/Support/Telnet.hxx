#pragma once

#include <string>
#include "Casts.hxx"

namespace Mud::Support::Telnet
{
    static const std::string NewLine("\r\n");

    enum class Control : uint8_t {
        Se = 240,
        Nop = 241,
        Dm = 242,
        Brk = 243,
        Ip = 244,
        Ao = 245,
        Ayt = 246,
        Ec = 247,
        El = 248,
        Ga = 249,
        Sb = 250,
        Will = 251,
        Wont = 252,
        Do = 253,
        Dont = 254,
        Iac = 255
    };

    enum class Option : uint8_t {
        Echo = 1,
        Suppress = 3,
        Status = 5,
        Timing = 6,
        TType = 24,
        Size = 31,
        TSpeed  = 32,
        RFlowCtrl = 33,
        LineMode = 34,
        EnvVar = 36
    };

    template <typename T>
    concept TelnetEnum = std::is_enum_v<T> &&
                         (std::is_same_v<T,Control> || std::is_same_v<T,Option>);

    template <TelnetEnum Head, TelnetEnum... Tail>
    std::string sequence(const Head head, Tail &&...tail)
    {
        std::string result(1, enum_cast(head));

        if constexpr (sizeof... (Tail))
            result += sequence(std::forward<Tail...>(tail...));

        return result;
    }
}
