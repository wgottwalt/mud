#pragma once

#include <fstream>
#include <iosfwd>
#include <mutex>
#include "Defaults.hxx"

namespace Mud::Log
{
    class Receiver {
    public:
        //--- public constructor ---
        Receiver(const Receiver &rhs) = delete;
        Receiver(Receiver &&rhs) = delete;

        //--- public operators ---
        Receiver &operator=(const Receiver &rhs) = delete;
        Receiver &operator=(Receiver &&rhs) = delete;

        //--- public methods ---
        static Receiver &instance(const std::string &path = DefaultPath,
                                  const std::string &info = DefaultInfo,
                                  const std::string &warn = DefaultWarn,
                                  const std::string &error = DefaultError,
                                  const std::string &fatal = DefaultFatal,
                                  const std::string &debug = DefaultDebug);
        void setLogToConsole(const bool on = true) noexcept;
        bool logToConsole() const noexcept;
        void setLogToFile(const bool on = true) noexcept;
        bool logToFile() const noexcept;
        std::string logFilePath(const Level level) const;
        void setConsoleOutput(std::ostream &os);
        void addEntry(const Entry &entry);

    protected:
        //--- protected constructors ---
        Receiver(const std::string &path, const std::string &info, const std::string &warn,
                 const std::string &error, const std::string &fatal, const std::string &debug);
        ~Receiver();

        //--- protected methods ---
        bool isLogToFileAvailable();

    private:
        //--- private properties ---
        const std::string _log_path;
        const std::string _info_name;
        const std::string _warn_name;
        const std::string _error_name;
        const std::string _fatal_name;
        const std::string _debug_name;
        std::ofstream _info_file;
        std::ofstream _warn_file;
        std::ofstream _error_file;
        std::ofstream _fatal_file;
        std::ofstream _debug_file;
        std::ostream &_console;
        std::mutex _file_mutex;
        std::mutex _console_mutex;
        bool _file_log_available;
        bool _log_to_console;
        bool _log_to_file;
    };
}
