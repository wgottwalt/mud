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
