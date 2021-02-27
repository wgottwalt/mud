#include <iostream>
#include "Connection.hxx"
#include "Support/String.hxx"

using namespace Mud::Net;
namespace S = Mud::Support::String;

//--- public constructors ---

Connection::Connection(TCP::socket &&socket)
: _socket(std::move(socket)), _removecb(nullptr), _interface(*this)
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
            std::cout << "server->client: " << S::trim(str) << std::endl;
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
                std::cout << "client->server: " << S::trim(line) << std::endl;
                _interface.process(line);

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
