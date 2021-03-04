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

List::List(const std::string &str, const std::string &separator)
: _data(std::move(split(str, separator)._data))
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

void List::clear() noexcept
{
    _data.clear();
}

bool List::empty() const noexcept
{
    return _data.empty();
}

void List::erase(const size_t pos) noexcept
{
    if (pos >= _data.size())
        return;

    auto it = _data.begin();
    std::advance(it, pos);
    _data.erase(it);
}

void List::erase(const size_t pos_from, const size_t pos_to) noexcept
{
    if (pos_from >= _data.size())
        return;

    if (pos_from > pos_to)
        return;

    auto it = _data.begin();

    if (pos_to >= _data.size())
    {
        std::advance(it, pos_from);
        _data.erase(it, _data.end());

        return;
    }

    auto it_to = _data.begin();

    std::advance(it, pos_from);
    std::advance(it_to, pos_to + 1);
    _data.erase(it, it_to);
}

std::string List::join(const std::string &separator) const
{
    return join(*this, separator);
}

size_t List::maxSize() const noexcept
{
    return _data.max_size();
}

size_t List::size() const noexcept
{
    return _data.size();
}

std::string List::join(const List &list, const std::string &separator)
{
    std::string result;

    if (list._data.size() > 1)
    {
        if (separator.empty())
        {
            for (auto &str : list._data)
            result += str;
        }
        else
        {
            auto last_it = list._data.end();

            --last_it;
            for (auto it = list._data.begin(); it != last_it; ++it)
                result += *it + separator;
            result += *last_it;
        }
    }
    else if (list.size() == 1)
        result = list._data.front();

    return result;
}

List List::split(const std::string &str, const std::string &separator)
{
    if (str.empty() && separator.empty())
        return List();

    List list;
    size_t last_pos = -separator.size();
    size_t pos = 0;

    do
    {
        last_pos += separator.size();
        pos = str.find_first_of(separator, pos + 2);
        list._data.emplace_back(str.substr(last_pos, pos - last_pos));
        last_pos = pos;
    }
    while (pos != std::string::npos);

    return list;
}
