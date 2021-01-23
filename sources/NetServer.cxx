#include <iostream>
#include "NetServer.hxx"

using namespace Mud::Net;

//--- public constructors ---

Server::Server(const uint16_t port)
: _connections(), _ioservice(), _sigset(_ioservice, SIGINT, SIGTERM), _socket(_ioservice),
  _acceptor(_ioservice, TCP::endpoint(TCP::v6(), port))
{
    _sigset.async_wait(
        [this](boost::system::error_code, const int32_t signal)
        {
            std::cout << "server: received signal " << signal << std::endl;
            _ioservice.stop();
            _connections.clear();
        });
}

Server::~Server()
{
}

//--- public methods ---

void Server::execute()
{
    std::cout << "server: up and running" << std::endl;
    accept();
    _ioservice.run();
}

//--- protected methods ---

void Server::accept()
{
    _acceptor.async_accept(_socket,
        [this](boost::system::error_code ec)
        {
            if (!ec)
            {
                decltype(_connections.begin()) connection;

                _connections.emplace_front(std::move(_socket));
                connection = _connections.begin();
                connection->setRemoveCallback(
                    [this,connection]()
                    {
                        _connections.erase(connection);
                        std::cout << "server: connection removed (" << _connections.size() << ")"
                                  << std::endl;
                    });

                std::cout << "server: connection from " << connection->socket().remote_endpoint()
                          << " (" << _connections.size() << ")" << std::endl;

                accept();
            }
        });
}
