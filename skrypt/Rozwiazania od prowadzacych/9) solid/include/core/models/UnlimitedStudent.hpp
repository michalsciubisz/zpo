#ifndef INCLUDE_CORE_MODELS_UNLIMITEDSTUDENT_HPP_
#define INCLUDE_CORE_MODELS_UNLIMITEDSTUDENT_HPP_

#include "Student.hpp"

namespace SystemCore {
    class UnlimitedStudent : public SystemCore::Student {
    public:
        UnlimitedStudent(std::string email_address, int university_id) :
                SystemCore::Student(email_address, university_id) {
            set_monthly_ebook_allowance(0);
        }
    };
}

#endif /* INCLUDE_CORE_MODELS_UNLIMITEDSTUDENT_HPP_ */
