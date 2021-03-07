#include <iostream>
#include <string>
#include "Support/Ansi.hxx"

namespace A = Mud::Support::Ansi;
using Font = A::Font;
using FG = A::Color::Foreground;
using BG = A::Color::Background;

constexpr auto seq = [](auto &&...args)
    { return A::sequence(std::forward<decltype(args)>(args)...); };

std::string ansi(auto color, const std::string &str)
{
    return seq(color, BG::Black) + str + seq(color, BG::White) + str + seq(Font::Reset);
}

int32_t main()
{
    std::cout << ansi(FG::Black, "Black") << ansi(FG::Red, "Red")
              << ansi(FG::Green, "Green") << ansi(FG::Yellow, "Yellow")
              << ansi(FG::Blue, "Blue") << ansi(FG::Magenta, "Magenta")
              << ansi(FG::Cyan, "Cyan") << ansi(FG::White, "White")
              << ansi(FG::BBlack, "BBlack") << ansi(FG::BRed, "BRed")
              << ansi(FG::BGreen, "BGreen") << ansi(FG::BYellow, "BYellow")
              << ansi(FG::BBlue, "BBlue") << ansi(FG::BMagenta, "BMagenta")
              << ansi(FG::BCyan, "BCyan") << ansi(FG::BWhite, "BWhite")
              << "\n"
              << ansi(Font::Bold, "Bold") << ansi(Font::Faint, "Faint")
              << ansi(Font::Italic, "Italic") << ansi(Font::Underline, "Underline")
              << ansi(Font::SlowBlink, "SlowBlink") << ansi(Font::RapidBlink, "RapidBlink")
              << std::endl;

    return 0;
}
