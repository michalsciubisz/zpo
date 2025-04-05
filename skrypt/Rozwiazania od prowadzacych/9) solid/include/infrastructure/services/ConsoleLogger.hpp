#ifndef SOLID_REFACTORING_REFACTORED_CONSOLELOGGER_HPP
#define SOLID_REFACTORING_REFACTORED_CONSOLELOGGER_HPP

#include <iostream>

#include "ILogger.hpp"

namespace SystemInfrastructure {
    class ConsoleLogger : public SystemCore::ILogger {
    public:
        void log(std::string message) {
            std::cout << message;
        }
    };
}

#endif //SOLID_REFACTORING_REFACTORED_CONSOLELOGGER_HPP
