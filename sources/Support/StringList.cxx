#include <iterator>
#include <stdexcept>
#include <utility>
#include "StringList.hxx"

using namespace Mud::Support::String;

//--- public constructors ---

List::List() noexcept
: _data()
{
}

List::List(const size_t count)
: _data(count)
{
}

List::List(const std::string &str)
: _data{str}
{
}

List::List(const size_t count, const std::string &str)
: _data(count, str)
{
}

List::List(std::string &&str)
: _data{std::move(str)}
{
}

List::List(const std::initializer_list<std::string> &list)
: _data(list)
{
}

List::List(const List &rhs)
: _data(rhs._data)
{
}

List::List(List &&rhs)
: _data(std::move(rhs._data))
{
}

List::~List() noexcept
{
}

//--- public operators ---

List &List::operator=(const List &rhs)
{
    if (this != &rhs)
        _data = rhs._data;

    return *this;
}

List &List::operator=(List &&rhs)
{
    if (this != &rhs)
        _data = std::move(rhs._data);

    return *this;
}

bool List::operator==(const List &rhs) const
{
    return _data == rhs._data;
}

bool List::operator!=(const List &rhs) const
{
    return !(*this == rhs);
}

//--- public methods ---

std::string &List::at(const size_t pos)
{
    if (pos >= _data.size())
        throw std::out_of_range("access element out of range");

    auto it = _data.begin();

    std::advance(it, pos);

    return *it;
}

std::string List::at(const size_t pos) const
{
    if (pos >= _data.size())
        throw std::out_of_range("access element out of range");

    auto it = _data.begin();

    std::advance(it, pos);

    return *it;
}

bool List::empty() const noexcept
{
    return _data.empty();
}

std::string List::join(const std::string &separator) const
{
    std::string result;

    if (_data.size() > 1)
    {
        if (separator.empty())
        {
            for (auto &str : _data)
                result += str;
        }
        else
        {
            auto last_it = _data.end();

            --last_it;
            for (auto it = _data.begin(); it != last_it; ++it)
                result += *it + separator;
            result += *last_it;
        }
    }
    else if (_data.size() == 1)
        result = _data.front();

    return result;
}

size_t List::maxSize() const noexcept
{
    return _data.max_size();
}

size_t List::size() const noexcept
{
    return _data.size();
}

void List::split(const std::string &str, const std::string &separator)
{
    if (str.empty() && separator.empty())
        return;

    std::list<std::string> result;
    size_t last_pos = -separator.size();
    size_t pos = 0;

    do
    {
        last_pos += separator.size();
        pos = str.find_first_of(separator, pos + 2);
        result.emplace_back(str.substr(last_pos, pos - last_pos));
        last_pos = pos;
    }
    while (pos != std::string::npos);

    _data.swap(result);
}