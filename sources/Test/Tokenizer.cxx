#include <iostream>
#include "Session/Tokenizer.hxx"

namespace S = Mud::Session;

int32_t main(int32_t argc, char **argv)
{
    std::string input;

    if (argc > 1)
    {
        for (int32_t i = 1; i < (argc - 1); ++i)
            input.append(argv[i]).append(" ");
        input += argv[argc - 1];

        S::Tokenizer t(input);
        std::string token;
        size_t i = 0;

        std::cout << "tokens: ";
        while (!(token = t.nextToken()).empty())
        {
            std::cout << "(" << i << ")" << token;
            ++i;
        }
        std::cout << std::endl;
    }

    return 0;
}