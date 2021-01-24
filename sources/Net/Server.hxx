#pragma once

#include <list>
#include "Connection.hxx"

namespace Mud::Net
{
    class Server {
    public:
        //--- public constructors ---
        Server(const uint16_t port = DefaultPort);
        Server(const Server &rhs) = delete;
        Server(Server &&rhs) = delete;
        ~Server();

        //--- public operators ---
        Server &operator=(const Server &rhs) = delete;
        Server &operator=(Server &&rhs) = delete;

        //--- public methods ---
        void execute();

    protected:
        //--- protected methods ---
        void accept();

    private:
        //--- private properties ---
        std::list<Connection> _connections;
        ASIO::io_service _ioservice;
        ASIO::signal_set _sigset;
        TCP::socket _socket;
        TCP::acceptor _acceptor;
    };
}
