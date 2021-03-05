#pragma once

#include <string>

namespace Mud::Session
{
    class Tokenizer {
    public:
        //--- public constructors ---
        Tokenizer(const std::string &str);
        Tokenizer(const Tokenizer &rhs);
        Tokenizer(Tokenizer &&rhs);
        ~Tokenizer();

        //--- public operators ---
        Tokenizer &operator=(const Tokenizer &rhs);
        Tokenizer &operator=(Tokenizer  &&rhs);
        bool operator==(const Tokenizer &rhs) const;
        bool operator!=(const Tokenizer &rhs) const;

        //--- public methods ---
        std::string nextToken();
        void reset(const std::string &str);
        void reset(std::string &&rhs);
        void reset();

    private:
        //--- private properties ---
        std::string _input;
        size_t _pos;
    };
}
