#include <iostream>
#include "Session/Tokenizer.hxx"
#include "Support/Concepts.hxx"
#include "Support/Telnet.hxx"

namespace S = Mud::Session;
namespace T = Mud::Support::Telnet;
using C = T::Control;
using O = T::Option;

constexpr auto seq = [](auto &&...args)
    { return T::sequence(std::forward<decltype(args)>(args)...); };

template <Mud::Support::Concepts::Integer I>
std::string gen(const I i, const S::Tokenizer::Token &token)
{
    std::string result("(" + std::to_string(i));

    if (token.type == S::Tokenizer::Type::Text)
    {
        result += "/STR)";
        result += token.seq;
    }
    else
    {
        result = "/TEL)";
        for (uint8_t chr : token.seq)
        {
            result += std::to_string(chr);
            result += " ";
        }
    }

    return result;
}

int32_t main(int32_t argc, char **argv)
{
    const std::string msg(seq(C::Iac) + seq(C::Sb) + seq(O::TType) + '\x01' + seq(C::Iac) +
                          seq(C::Se));
    std::string input;

    if (argc > 1)
    {
        for (int32_t i = 1; i < (argc - 1); ++i)
            input.append(argv[i]).append(" ");
        input += argv[argc - 1];
        input += msg;

        S::Tokenizer t(input);
        S::Tokenizer::Token token;
        size_t i = 0;

        std::cout << "tokens: ";
        while (!(token = t.nextToken()).seq.empty())
        {
            std::cout << gen(i, token);
            ++i;
        }
        std::cout << std::endl;
    }

    return 0;
}
