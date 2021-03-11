#pragma once

#include <string>

namespace Mud::Session
{
    class Tokenizer {
    public:
        //--- public types and constants ---
        enum class Type : uint8_t {
            Text,
            Telnet
        };

        struct Token {
            std::string seq;
            Type type;
        };

        //--- public constructors ---
        Tokenizer(const std::string &str);
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
        Token nextToken();
        void reset(const std::string &str);
        void reset(std::string &&rhs) noexcept;
        void reset() noexcept;

    protected:
        //--- protected methods ---
        void readTelnetSequence(std::string::iterator &it, Token &token) const;

    private:
        //--- private properties ---
        std::string _input;
        size_t _pos;
    };
}
