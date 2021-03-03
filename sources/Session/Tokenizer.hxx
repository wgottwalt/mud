#pragma once

#include "Support/StringList.hxx"

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
        void tokenize(const std::string &str);
        std::string nextToken();
        void reset();

    private:
        //--- private properties ---
        Support::String::List _input;
        size_t _current_token;
    };
}
