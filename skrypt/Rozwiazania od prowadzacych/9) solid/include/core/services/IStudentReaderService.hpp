#ifndef INCLUDE_CORE_SERVICES_ISTUDENTREADERSERVICE_HPP_
#define INCLUDE_CORE_SERVICES_ISTUDENTREADERSERVICE_HPP_

#include <vector>

#include "Student.hpp"

namespace SystemCore {
    class IStudentReaderService {
        virtual std::vector<SystemCore::Student*> get_students_by_university() = 0;
        virtual std::vector<SystemCore::Student*> get_students_by_currently_borrowed_ebooks() = 0;
    };
}

#endif /* INCLUDE_CORE_SERVICES_ISTUDENTREADERSERVICE_HPP_ */
