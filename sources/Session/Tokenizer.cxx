#include <utility>
#include "Tokenizer.hxx"

using namespace Mud::Session;

//--- public constructors ---

Tokenizer::Tokenizer(const std::string &str)
: _input(str, " "), _current_token(0)
{
}

Tokenizer::Tokenizer(const Tokenizer &rhs)
: _input(rhs._input), _current_token(rhs._current_token)
{
}

Tokenizer::Tokenizer(Tokenizer &&rhs)
: _input(std::move(rhs._input)), _current_token(std::move(rhs._current_token))
{
}

Tokenizer::~Tokenizer()
{
}

//--- public operators ---

Tokenizer &Tokenizer::operator=(const Tokenizer &rhs)
{
    if (this != &rhs)
    {
        _input = rhs._input;
        _current_token = rhs._current_token;
    }

    return *this;
}

Tokenizer &Tokenizer::operator=(Tokenizer  &&rhs)
{
    if (this != &rhs)
    {
        _input = std::move(rhs._input);
        _current_token = std::move(rhs._current_token);
    }

    return *this;
}

bool Tokenizer::operator==(const Tokenizer &rhs) const
{
    return _input == rhs._input &&
           _current_token == rhs._current_token;
}

bool Tokenizer::operator!=(const Tokenizer &rhs) const
{
    return !(*this == rhs);
}

//--- public methods ---

void Tokenizer::tokenize(const std::string &str)
{
    if (str.empty())
        return;

    _input = { str, " " };
    _current_token = 0;
}

std::string Tokenizer::nextToken()
{
    std::string result;

    if (_input.size() > _current_token)
    {
        result = _input.at(_current_token);
        ++_current_token;
    }

    return result;
}

void Tokenizer::reset()
{
    _current_token = 0;
}
