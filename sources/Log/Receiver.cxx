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

void Receiver::addEntry(const Entry &entry)
{
    if (_log_to_console && _log_to_file)
    {
        const std::string msg(STR::str("[", TIME::toDateString(entry.stamp), "][",
                              levelToString(entry.level), "][", entry.component, "]: ",
                              entry.message, "\n"));

        if (_log_to_console)
        {
            std::lock_guard<std::mutex> lock(_console_mutex);

            _console << msg;
        }

        if (_log_to_file)
        {
            std::ostream *ofile = nullptr;

            switch (entry.level)
            {
                case Level::Info:
                    ofile = &_info_file;
                    break;

                case Level::Warn:
                    ofile = &_warn_file;
                    break;

                case Level::Error:
                    ofile = &_error_file;
                    break;

                case Level::Fatal:
                    ofile = &_fatal_file;
                    break;

                case Level::Debug:
                default:
                    ofile = &_debug_file;
            }
            {
                std::lock_guard<std::mutex> lock(_file_mutex);

                *ofile << msg;
            }
        }
    }
}

//--- protected constructors ---

Receiver::Receiver(const std::string &path, const std::string &info, const std::string &warn,
                   const std::string &error, const std::string &fatal, const std::string &debug)
: _log_path(path), _info_name(info), _warn_name(warn), _error_name(error), _fatal_name(fatal),
  _debug_name(debug), _console(std::cout), _file_mutex(), _console_mutex(),
  _file_log_available(isLogToFileAvailable()), _log_to_console(true),
  _log_to_file(_file_log_available)
{
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
        _info_file.open(_log_path + "/" + _info_name);
        _warn_file.open(_log_path + "/" + _warn_name);
        _error_file.open(_log_path + "/" + _error_name);
        _fatal_file.open(_log_path + "/" + _fatal_name);
        _debug_file.open(_log_path + "/" + _debug_name);

        if (_info_file && _warn_file && _error_file && _fatal_file && _debug_file)
            return true;
    }

    return false;
}
