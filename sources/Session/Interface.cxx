#include "Interface.hxx"
#include "Defaults.hxx"
#include "Net/Connection.hxx"
#include "Support/String.hxx"

using namespace Mud::Session;
namespace S = Mud::Support::String;
namespace T = Mud::Session::Telnet;

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
            _connection.send(S::str("Test MUD!", T::NL));
            _connection.send("username: ");
            _state = State::Username;
            break;

        case State::Username:
            _connection.send(S::str(T::EOFF, "password: "));
            _username = S::trim(input);
            _state = State::Password;
            break;

        case State::Password:
            _connection.send(S::str(T::EON, T::NL, "logged in...", T::NL));
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
