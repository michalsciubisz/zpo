#ifndef INCLUDE_CORE_MODELS_LIMITEDSTUDENT_HPP_
#define INCLUDE_CORE_MODELS_LIMITEDSTUDENT_HPP_

#include <string>

#include "Student.hpp"
#include "IBonusAllowable.hpp"

namespace SystemCore {
    class LimitedStudent : public SystemCore::Student, public SystemCore::IBonusAllowable {
    public:
        LimitedStudent(std::string email_address, int university_id) :
                SystemCore::Student(email_address, university_id) {
        }
    };
}

#endif /* INCLUDE_CORE_MODELS_LIMITEDSTUDENT_HPP_ */
