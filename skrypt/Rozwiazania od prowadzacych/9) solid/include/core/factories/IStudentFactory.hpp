#ifndef ISTUDENTFACTORY_HPP_
#define ISTUDENTFACTORY_HPP_

#include <string>
#include <memory>

#include "Student.hpp"
#include "PackageType.hpp"

namespace SystemCore {
    class IStudentFactory {
    public:
        virtual std::unique_ptr<SystemCore::Student> create(std::string email_address,
                                                            int university_id, SystemCore::PackageType package) = 0;
    };
}

#endif /* ISTUDENTFACTORY_HPP_ */
