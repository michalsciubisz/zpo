#ifndef INCLUDE_CORE_EXCEPTIONS_NOTIMPLEMENTEDEXCEPTION_HPP_
#define INCLUDE_CORE_EXCEPTIONS_NOTIMPLEMENTEDEXCEPTION_HPP_

#include <stdexcept>
#include "exceptions/DomainException.hpp"

namespace SystemCore {
    class NotImplementedException : public DomainException {
    public:
        NotImplementedException() : DomainException(std::string("Function not yet implemented.")) {}
    };
}

#endif /* INCLUDE_CORE_EXCEPTIONS_NOTIMPLEMENTEDEXCEPTION_HPP_ */
