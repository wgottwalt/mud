#pragma once

#include <functional>
#include <iosfwd>
#include <string>
#include "NetDefaults.hxx"

namespace Mud::Net
{
    class Connection {
    public:
        //--- public types and constants ---
        using RemoveCallback = std::function<void()>;

        //--- public constructors ---
        Connection(TCP::socket &&socket);
        Connection(const Connection &rhs) = delete;
        Connection(Connection &&rhs) = delete;
        virtual ~Connection();

        //--- public operators ---
        Connection &operator=(const Connection &rhs) = delete;
        Connection &operator=(Connection &&rhs) = delete;

        //--- public methods ---
        void send(const std::string &str);
        void receive();
        void setRemoveCallback(RemoveCallback &&cb);
        void executeRemoveCallback();
        TCP::socket &socket();

    private:
        //--- private properties ---
        TCP::socket _socket;
        RemoveCallback _removecb;
    };
}
