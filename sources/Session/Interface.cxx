#include "Interface.hxx"
#include "Net/Connection.hxx"
#include "Support/String.hxx"

using namespace Mud::Session;
namespace S = Mud::Support::String;

//--- public constructors ---

Interface::Interface(Net::Connection &connection)
: _connection(connection), _state(State::New)
{
    process();
}

Interface::~Interface()
{
}

//--- public methods ---

void Interface::process(const std::string &input)
{
    switch (_state)
    {
        case State::New:
            _connection.send("Test MUD!\r\n");
            _connection.send("username: ");
            _state = State::Username;
            break;

        case State::Username:
            _connection.send("password: ");
            _username = S::trim(input);
            _state = State::Password;
            break;

        case State::Password:
            _connection.send("logged in...\r\n");
            _connection.send(_username + "> ");
            _password = S::trim(input);
            _state = State::Established;
            break;

        case State::Established:
            break;
    }
}
