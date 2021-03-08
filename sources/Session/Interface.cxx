#include "Interface.hxx"
#include "Net/Connection.hxx"
#include "Support/Ansi.hxx"
#include "Support/String.hxx"
#include "Support/Telnet.hxx"

using namespace Mud::Session;
namespace A = Mud::Support::Ansi;
namespace S = Mud::Support::String;
namespace T = Mud::Support::Telnet;

//--- internal stuff ---

namespace Mud::Support::Telnet
{
    const std::string EchoOff("");
    const std::string EchoOn("");
}

//--- public constructors ---

Interface::Interface(Net::Connection &connection)
: _connection(connection), _username(), _password(), _state(State::New), _passed(false)
{
    process();
}

Interface::~Interface() noexcept
{
}

//--- public methods ---

void Interface::process(const std::string &input)
{
    switch (_state)
    {
        case State::New:
            _connection.send(S::str("Test MUD!", T::NewLine));
            _connection.send("username: ");
            _state = State::Username;
            break;

        case State::Username:
            _connection.send(S::str(T::EchoOff, "password: "));
            _username = S::trim(input);
            _state = State::Password;
            break;

        case State::Password:
            _connection.send(S::str(T::EchoOn, T::NewLine, "logged in...", T::NewLine));
            _connection.send(_username + "> ");
            _password = S::trim(input);
            _state = State::Established;
            break;

        case State::Established:
            _connection.send(S::str(_username, " (", S::trim(input), ")> "));
            break;
    }
}

bool Interface::validLogin() const noexcept
{
    return !_username.empty() && !_password.empty() && _passed;
}
