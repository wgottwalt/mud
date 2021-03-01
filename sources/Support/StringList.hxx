#pragma once

#include <initializer_list>
#include <list>
#include <string>

namespace Mud::Support::String
{
    class List {
    public:
        //--- public constructors ---
        List() noexcept;
        List(const size_t count);
        List(const std::string &str);
        List(const size_t count, const std::string &str);
        List(std::string &&str);
        List(const std::initializer_list<std::string> &list);
        List(const List &rhs);
        List(List &&rhs);
        ~List() noexcept;

        //--- public operators ---
        List &operator=(const List &rhs);
        List &operator=(List &&rhs);
        bool operator==(const List &rhs) const;
        bool operator!=(const List &rhs) const;

        //--- public methods ---
        std::string &at(const size_t pos);
        std::string at(const size_t pos) const;
        bool empty() const noexcept;
        size_t maxSize() const noexcept;
        size_t size() const noexcept;

    private:
        //--- private properties ---
        std::list<std::string> _data;
    };
}
