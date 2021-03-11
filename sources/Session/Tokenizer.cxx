#include <utility>
#include "Tokenizer.hxx"
#include "Support/Casts.hxx"
#include "Support/Telnet.hxx"

using namespace Mud::Session;
namespace T = Mud::Support::Telnet;
using TC = T::Control;

//--- public constructors ---

Tokenizer::Tokenizer(const std::string &str)
: _input(str), _pos(0)
{
}

Tokenizer::Tokenizer(const Tokenizer &rhs)
: _input(rhs._input), _pos(rhs._pos)
{
}

Tokenizer::Tokenizer(Tokenizer &&rhs) noexcept
: _input(std::move(rhs._input)), _pos(std::move(rhs._pos))
{
}

Tokenizer::~Tokenizer() noexcept
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

Tokenizer &Tokenizer::operator=(Tokenizer &&rhs) noexcept
{
    if (this != &rhs)
    {
        _input = std::move(rhs._input);
        _pos = std::move(rhs._pos);
    }

    return *this;
}

bool Tokenizer::operator==(const Tokenizer &rhs) const noexcept
{
    return _input == rhs._input &&
           _pos == rhs._pos;
}

bool Tokenizer::operator!=(const Tokenizer &rhs) const noexcept
{
    return !(*this == rhs);
}

//--- public methods ---

std::string Tokenizer::input() const noexcept
{
    return _input;
}

Tokenizer::Token Tokenizer::nextToken()
{
    Token result{"", Type::Text};
    std::string::iterator it = std::next(_input.begin(), _pos);
    bool done = false;

    while (it != _input.end())
    {
        if (std::isalnum(*it))
        {
            if (done)
                break;
            result.seq += *it;
        }
        else if (static_cast<uint8_t>(*it) == enum_cast(TC::Iac))
        {
            if (result.seq.empty())
            {
                result.seq += *it;
                result.type = Type::Telnet;
                readTelnetSequence(++it, result);
            }

            break;
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

void Tokenizer::reset(std::string &&str) noexcept
{
    if (!str.empty())
    {
        _input = std::move(str);
        _pos = 0;
    }
}

void Tokenizer::reset() noexcept
{
    _pos = 0;
}

//--- protected methods ---

void Tokenizer::readTelnetSequence(std::string::iterator &it, Token &token) const
{
    while (T::istelnet(*it))
    {
        token.seq += *it;

        if (*it == enum_cast(TC::Se))
        {
            ++it;
            break;
        }

        ++it;
    }
}
