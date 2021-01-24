#include <iostream>
#include "Log/Receiver.hxx"

namespace L = Mud::Log;
namespace T = Mud::Support::Time;

int32_t main()
{
    auto &log = L::Receiver::instance();

    std::cout << "console logging: " << (log.logToConsole() ? "yes" : "no") << "\n"
              << "file logging:    " << (log.logToFile() ? "yes" : "no") << "\n"
              << "info log file:   " << log.logFilePath(L::Level::Info) << "\n"
              << "warn log file:   " << log.logFilePath(L::Level::Warn) << "\n"
              << "error log file:  " << log.logFilePath(L::Level::Error) << "\n"
              << "fatal log file:  " << log.logFilePath(L::Level::Fatal) << "\n"
              << "debug log file:  " << log.logFilePath(L::Level::Debug) << "\n"
              << std::endl;

    log.addEntry({L::Level::Info, T::now(), "undefined", "test info message"});

    return 0;
}
