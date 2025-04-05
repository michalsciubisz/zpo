#ifndef DOMAINEXCEPTION_HPP_
#define DOMAINEXCEPTION_HPP_

#include <exception>
#include <string>

namespace SystemCore {
    class DomainException : public std::exception {
    private:
        std::string message_;
    public:
        DomainException(std::string message) :
                message_(message) {

        }
        const char* what() const noexcept override {
            return message_.c_str();
        }
    };
}

#endif /* DOMAINEXCEPTION_HPP_ */
