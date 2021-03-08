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
        List(const std::string &str, const std::string &separator);
        List(std::string &&str) noexcept;
        List(const std::initializer_list<std::string> &list);
        List(const List &rhs);
        List(List &&rhs) noexcept;
        ~List() noexcept;

        //--- public operators ---
        List &operator=(const List &rhs);
        List &operator=(List &&rhs) noexcept;
        bool operator==(const List &rhs) const noexcept;
        bool operator!=(const List &rhs) const noexcept;

        //--- public methods ---
        std::string &at(const size_t pos);
        std::string at(const size_t pos) const;
        void clear() noexcept;
        bool empty() const noexcept;
        void erase(const size_t pos) noexcept;
        void erase(const size_t pos_from, const size_t pos_to) noexcept;
        std::string join(const std::string &separator = " ") const;
        size_t maxSize() const noexcept;
        size_t size() const noexcept;

        static std::string join(const List &list, const std::string &separator = " ");
        static List split(const std::string &str, const std::string &seperator = " ");

    private:
        //--- private properties ---
        std::list<std::string> _data;
    };
}
