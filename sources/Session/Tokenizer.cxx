#include <utility>
#include "Tokenizer.hxx"

using namespace Mud::Session;

//--- public constructors ---

Tokenizer::Tokenizer(const std::string &str)
: _input(str), _pos(0)
{
}

Tokenizer::Tokenizer(const Tokenizer &rhs)
: _input(rhs._input), _pos(rhs._pos)
{
}

Tokenizer::Tokenizer(Tokenizer &&rhs)
: _input(std::move(rhs._input)), _pos(std::move(rhs._pos))
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
        _pos = rhs._pos;
    }

    return *this;
}

Tokenizer &Tokenizer::operator=(Tokenizer &&rhs)
{
    if (this != &rhs)
    {
        _input = std::move(rhs._input);
        _pos = std::move(rhs._pos);
    }

    return *this;
}

bool Tokenizer::operator==(const Tokenizer &rhs) const
{
    return _input == rhs._input &&
           _pos == rhs._pos;
}

bool Tokenizer::operator!=(const Tokenizer &rhs) const
{
    return !(*this == rhs);
}

//--- public methods ---

std::string Tokenizer::nextToken()
{
    std::string result;
    std::string::iterator it = std::next(_input.begin(), _pos);
    bool done = false;

    while (it != _input.end())
    {
        if (!std::isspace(*it))
        {
            if (done)
                break;
            result += *it;
        }
        else
            done = true;

        ++it;
    }
    _pos = std::distance(_input.begin(), it);

    return result;
}

void Tokenizer::reset(const std::string &str)
{
    if (!str.empty())
    {
        _input = str;
        _pos = 0;
    }
}

void Tokenizer::reset(std::string &&str)
{
    if (!str.empty())
    {
        _input = std::move(str);
        _pos = 0;
    }
}

void Tokenizer::reset()
{
    _pos = 0;
}
