#ifndef INCLUDE_CORE_SERVICES_ISTUDENTWRITERSERVICE_HPP_
#define INCLUDE_CORE_SERVICES_ISTUDENTWRITERSERVICE_HPP_

#include <string>

#include "University.hpp"

namespace SystemCore {
    class IStudentWriterService {
        virtual void add(std::string email_address, SystemCore::UniversityID universityId) = 0;
        virtual void add_bonus_allowances() = 0;
    };
}

#endif /* INCLUDE_CORE_SERVICES_ISTUDENTWRITERSERVICE_HPP_ */
