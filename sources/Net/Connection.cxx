#include <iostream>
#include "Connection.hxx"

using namespace Mud::Net;

//--- public constructors ---

Connection::Connection(TCP::socket &&socket)
: _socket(std::move(socket)), _removecb(nullptr)
{
    receive();
}

Connection::~Connection()
{
    _socket.cancel();
}

//--- public methods ---

void Connection::send(const std::string &str)
{
    auto buffer = std::make_shared<ASIO::streambuf>();
    std::ostream strm(buffer.get());

    strm << str;

    async_write(_socket, *buffer,
        [this,buffer,str](boost::system::error_code, size_t)
        {
        });
}

void Connection::receive()
{
    auto buffer = std::make_shared<ASIO::streambuf>();

    async_read_until(_socket, *buffer, '\n',
        [this,buffer](boost::system::error_code ec, size_t)
        {
            if (!ec)
            {
                std::istream strm(buffer.get());
                std::string line;

                std::getline(strm, line);
                std::cout << "client->server: " << line << std::endl;
                receive();
                return;
            }
            executeRemoveCallback();
        });
}

void Connection::setRemoveCallback(RemoveCallback &&cb)
{
    _removecb = std::forward<RemoveCallback>(cb);
}

void Connection::executeRemoveCallback()
{
    _removecb();
}

TCP::socket &Connection::socket()
{
    return _socket;
}
