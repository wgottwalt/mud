#include <filesystem>
#include <iostream>
#include "Receiver.hxx"
#include "Support/String.hxx"

using namespace Mud::Log;
namespace FS = std::filesystem;
namespace TIME = Mud::Support::Time;
namespace STR = Mud::Support::String;

//--- public methods ---

Receiver &Receiver::instance(const std::string &path, const std::string &info,
                             const std::string &warn, const std::string &error,
                             const std::string &fatal, const std::string &debug)
{
    static Receiver __instance(path, info, warn, error, fatal, debug);

    return __instance;
}

void Receiver::setLogToConsole(const bool on) noexcept
{
    _log_to_console = on;
}

bool Receiver::logToConsole() const noexcept
{
    return _log_to_console;
}

void Receiver::setLogToFile(const bool on) noexcept
{
    _log_to_file = _file_log_available ? on : false;
}

bool Receiver::logToFile() const noexcept
{
    return _file_log_available;
}

std::string Receiver::logFilePath(const Level level) const
{
    switch (level)
    {
        case Level::Info:
            return _log_path + "/" + _info_name;

        case Level::Warn:
            return _log_path + "/" + _warn_name;

        case Level::Error:
            return _log_path + "/" + _error_name;

        case Level::Fatal:
            return _log_path + "/" + _fatal_name;

        case Level::Debug:
        default:
            return _log_path + "/" + _debug_name;
    }
}

void Receiver::setConsoleOutput(std::ostream &os)
{
    _console.rdbuf(os.rdbuf());
}

void Receiver::addEntry(Entry &&entry)
{
    if (!_log_to_console && !_log_to_file)
        return;

    switch (entry.level)
    {
        case Level::Info:
            processInfo(std::move(entry));
            break;

        case Level::Warn:
            processWarn(std::move(entry));
            break;

        case Level::Error:
            processError(std::move(entry));
            break;

        case Level::Fatal:
            processFatal(std::move(entry));
            break;

        case Level::Debug:
        default:
            processDebug(std::move(entry));
    }
}

//--- protected constructors ---

Receiver::Receiver(const std::string &path, const std::string &info, const std::string &warn,
                   const std::string &error, const std::string &fatal, const std::string &debug)
: _log_path(path), _info_name(info), _warn_name(warn), _error_name(error), _fatal_name(fatal),
  _debug_name(debug), _console(std::cout), _mutexes(), _file_log_available(isLogToFileAvailable()),
  _log_to_console(true), _log_to_file(_file_log_available)
{
    if (_log_to_file)
    {
        const std::string startmsg = STR::str("[", TIME::toDateString(TIME::now()), "] -----\n");

        _info_file << startmsg;
        _warn_file << startmsg;
        _error_file << startmsg;
        _fatal_file << startmsg;
        _debug_file << startmsg;
    }
}

Receiver::~Receiver()
{
}

//--- protected methods ---

bool Receiver::isLogToFileAvailable()
{
    if (!FS::exists(_log_path))
        FS::create_directory(_log_path);

    if (FS::exists(_log_path) && FS::is_directory(_log_path))
    {
        _info_file.open(_log_path + "/" + _info_name, std::ios::app);
        _warn_file.open(_log_path + "/" + _warn_name, std::ios::app);
        _error_file.open(_log_path + "/" + _error_name, std::ios::app);
        _fatal_file.open(_log_path + "/" + _fatal_name, std::ios::app);
        _debug_file.open(_log_path + "/" + _debug_name, std::ios::app);

        if (_info_file && _warn_file && _error_file && _fatal_file && _debug_file)
            return true;
    }

    return false;
}

void Receiver::processInfo(Entry &&entry)
{
    const std::string msg(STR::str("[", TIME::toDateString(entry.stamp), "][info ][",
                          entry.component, "]: ", entry.message, "\n"));

    if (_log_to_console)
    {
        std::lock_guard<std::mutex> lock(_mutexes[5]);
        _console << msg;
    }

    if (_log_to_file)
    {
        std::lock_guard<std::mutex> lock(_mutexes[0]);
        _info_file << msg;
    }
}

void Receiver::processWarn(Entry &&entry)
{
    const std::string msg(STR::str("[", TIME::toDateString(entry.stamp), "][warn ][",
                          entry.component, "]: ", entry.message, "\n"));

    if (_log_to_console)
    {
        std::lock_guard<std::mutex> lock(_mutexes[5]);
        _console << msg;
    }

    if (_log_to_file)
    {
        std::lock_guard<std::mutex> lock(_mutexes[1]);
        _warn_file << msg;
    }
}

void Receiver::processError(Entry &&entry)
{
    const std::string msg(STR::str("[", TIME::toDateString(entry.stamp), "][error][",
                          entry.component, "]: ", entry.message, "\n"));

    if (_log_to_console)
    {
        std::lock_guard<std::mutex> lock(_mutexes[5]);
        _console << msg;
    }

    if (_log_to_file)
    {
        std::lock_guard<std::mutex> lock(_mutexes[2]);
        _error_file << msg;
    }
}

void Receiver::processFatal(Entry &&entry)
{
    const std::string msg(STR::str("[", TIME::toDateString(entry.stamp), "][fatal][",
                          entry.component, "]: ", entry.message, "\n"));

    if (_log_to_console)
    {
        std::lock_guard<std::mutex> lock(_mutexes[5]);
        _console << msg;
    }

    if (_log_to_file)
    {
        std::lock_guard<std::mutex> lock(_mutexes[3]);
        _fatal_file << msg;
    }
}

void Receiver::processDebug(Entry &&entry)
{
    const std::string msg(STR::str("[", TIME::toDateString(entry.stamp), "][debug][",
                          entry.component, "]: ", entry.message, "\n"));

    if (_log_to_console)
    {
        std::lock_guard<std::mutex> lock(_mutexes[5]);
        _console << msg;
    }

    if (_log_to_file)
    {
        std::lock_guard<std::mutex> lock(_mutexes[4]);
        _debug_file << msg;
    }
}
