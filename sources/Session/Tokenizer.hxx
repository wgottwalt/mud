#pragma once

#include <string>

namespace Mud::Session
{
    class Tokenizer {
    public:
        //--- public constructors ---
        Tokenizer(const std::string &str, const bool ascii = true);
        Tokenizer(const Tokenizer &rhs);
        Tokenizer(Tokenizer &&rhs) noexcept;
        ~Tokenizer() noexcept;

        //--- public operators ---
        Tokenizer &operator=(const Tokenizer &rhs);
        Tokenizer &operator=(Tokenizer  &&rhs) noexcept;
        bool operator==(const Tokenizer &rhs) const noexcept;
        bool operator!=(const Tokenizer &rhs) const noexcept;

        //--- public methods ---
        std::string input() const noexcept;
        bool ascii() const noexcept;
        std::string nextToken();
        void reset(const std::string &str, const bool ascii = true);
        void reset(std::string &&rhs, const bool ascii = true) noexcept;
        void reset(const bool ascii = true) noexcept;

    private:
        //--- private properties ---
        std::string _input;
        size_t _pos;
        bool _ascii;
    };
}
