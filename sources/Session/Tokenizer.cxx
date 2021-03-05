#include <utility>
#include "Tokenizer.hxx"

using namespace Mud::Session;

//--- public constructors ---

Tokenizer::Tokenizer(const std::string &str, const bool ascii)
: _input(str), _pos(0), _ascii(ascii)
{
}

Tokenizer::Tokenizer(const Tokenizer &rhs)
: _input(rhs._input), _pos(rhs._pos), _ascii(rhs._ascii)
{
}

Tokenizer::Tokenizer(Tokenizer &&rhs)
: _input(std::move(rhs._input)), _pos(std::move(rhs._pos)), _ascii(std::move(rhs._ascii))
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
        _ascii = rhs._ascii;
    }

    return *this;
}

Tokenizer &Tokenizer::operator=(Tokenizer &&rhs)
{
    if (this != &rhs)
    {
        _input = std::move(rhs._input);
        _pos = std::move(rhs._pos);
        _ascii = std::move(rhs._ascii);
    }

    return *this;
}

bool Tokenizer::operator==(const Tokenizer &rhs) const
{
    return _input == rhs._input &&
           _pos == rhs._pos &&
           _ascii == rhs._ascii;
}

bool Tokenizer::operator!=(const Tokenizer &rhs) const
{
    return !(*this == rhs);
}

//--- public methods ---

std::string Tokenizer::input() const
{
    return _input;
}

bool Tokenizer::ascii() const
{
    return _ascii;
}

std::string Tokenizer::nextToken()
{
    std::string result;
    std::string::iterator it = std::next(_input.begin(), _pos);
    bool done = false;

    if (_ascii)
    {
        while (it != _input.end())
        {
            if (std::isgraph(*it))
            {
                if (done)
                    break;
                result += *it;
            }
            else
                done = true;

            ++it;
        }
    }
    else
    {
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
    }
    _pos = std::distance(_input.begin(), it);

    return result;
}

void Tokenizer::reset(const std::string &str, const bool ascii)
{
    if (!str.empty())
    {
        _input = str;
        _pos = 0;
        _ascii = ascii;
    }
}

void Tokenizer::reset(std::string &&str, const bool ascii)
{
    if (!str.empty())
    {
        _input = std::move(str);
        _pos = 0;
        _ascii = ascii;
    }
}

void Tokenizer::reset(const bool ascii)
{
    _pos = 0;
    _ascii = ascii;
}
