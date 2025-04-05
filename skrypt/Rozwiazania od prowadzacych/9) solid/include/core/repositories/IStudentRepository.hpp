#ifndef INCLUDE_CORE_REPOSITORIES_ISTUDENTREPOSITORY_HPP_
#define INCLUDE_CORE_REPOSITORIES_ISTUDENTREPOSITORY_HPP_

#include <string>
#include <vector>
#include <memory>

#include "Student.hpp"
#include "LimitedStudent.hpp"

namespace SystemCore {
    class IStudentRepository {
    public:
        virtual void add(std::unique_ptr<SystemCore::Student> student) = 0;
        virtual bool exists(std::string email_address) const = 0;
        virtual std::vector<LimitedStudent*> get_students_for_allowance_increase() = 0;
    };
}

#endif /* INCLUDE_CORE_REPOSITORIES_ISTUDENTREPOSITORY_HPP_ */
