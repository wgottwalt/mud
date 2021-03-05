#pragma once

#include <string>

namespace Mud::Session
{
    class Tokenizer {
    public:
        //--- public constructors ---
        Tokenizer(const std::string &str, const bool ascii = true);
        Tokenizer(const Tokenizer &rhs);
        Tokenizer(Tokenizer &&rhs);
        ~Tokenizer();

        //--- public operators ---
        Tokenizer &operator=(const Tokenizer &rhs);
        Tokenizer &operator=(Tokenizer  &&rhs);
        bool operator==(const Tokenizer &rhs) const;
        bool operator!=(const Tokenizer &rhs) const;

        //--- public methods ---
        std::string input() const;
        bool ascii() const;
        std::string nextToken();
        void reset(const std::string &str, const bool ascii = true);
        void reset(std::string &&rhs, const bool ascii = true);
        void reset(const bool ascii = true);

    private:
        //--- private properties ---
        std::string _input;
        size_t _pos;
        bool _ascii;
    };
}
