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
        TSize = 31,
        TSpeed = 32,
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

    template <Concepts::Number T>
    constexpr bool istelnet(const T val)
    {
        switch (val)
        {
            case static_cast<T>(Control::Se):
            case static_cast<T>(Control::Nop):
            case static_cast<T>(Control::Dm):
            case static_cast<T>(Control::Brk):
            case static_cast<T>(Control::Ip):
            case static_cast<T>(Control::Ao):
            case static_cast<T>(Control::Ayt):
            case static_cast<T>(Control::Ec):
            case static_cast<T>(Control::El):
            case static_cast<T>(Control::Ga):
            case static_cast<T>(Control::Sb):
            case static_cast<T>(Control::Will):
            case static_cast<T>(Control::Wont):
            case static_cast<T>(Control::Do):
            case static_cast<T>(Control::Dont):
            case static_cast<T>(Control::Iac):
            case static_cast<T>(Option::Echo):
            case static_cast<T>(Option::Suppress):
            case static_cast<T>(Option::Status):
            case static_cast<T>(Option::Timing):
            case static_cast<T>(Option::TType):
            case static_cast<T>(Option::TSize):
            case static_cast<T>(Option::TSpeed):
            case static_cast<T>(Option::RFlowCtrl):
            case static_cast<T>(Option::LineMode):
            case static_cast<T>(Option::EnvVar):
                return true;
            default:
                return false;
        }
    }
}
