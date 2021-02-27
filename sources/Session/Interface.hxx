#pragma once

#include <string>

namespace Mud::Net
{
    class Connection;
}

namespace Mud::Session
{
    enum class State : int8_t {
        New,
        Username,
        Password,
        Established
    };

    class Interface {
    public:
        //--- public constructors ---
        Interface(Net::Connection &connection);
        Interface(const Interface &rhs) = delete;
        Interface(Interface &&rhs) = delete;
        ~Interface();

        //--- public operators ---
        Interface &operator=(const Interface &rhs) = delete;
        Interface &operator=(Interface &&rhs) = delete;

        //--- public methods ---
        void process(const std::string &input = "");

    private:
        //--- private properties ---
        Net::Connection &_connection;
        std::string _username;
        std::string _password;
        State _state;
    };
}
