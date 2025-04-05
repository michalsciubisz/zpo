#ifndef INCLUDE_CORE_SERVICES_ILOGGER_HPP_
#define INCLUDE_CORE_SERVICES_ILOGGER_HPP_

#include <string>

namespace SystemCore {
    class ILogger {
    public:
        virtual void log(std::string message) = 0;
    };
}

#endif /* INCLUDE_CORE_SERVICES_ILOGGER_HPP_ */
