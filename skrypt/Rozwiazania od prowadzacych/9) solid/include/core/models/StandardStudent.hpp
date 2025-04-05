#ifndef INCLUDE_CORE_MODELS_STANDARDSTUDENT_HPP_
#define INCLUDE_CORE_MODELS_STANDARDSTUDENT_HPP_

#include <string>

#include "LimitedStudent.hpp"

namespace SystemCore {
    class StandardStudent : public LimitedStudent {
    public:
        StandardStudent(std::string email_address, int university_id) :
                LimitedStudent(email_address, university_id) {
            set_monthly_ebook_allowance(Student::STANDARD_ALLOWANCE);
        }

        void add_bonus_allowance() override {
            set_monthly_ebook_allowance(get_monthly_ebook_allowance() + 5);
        }
    };
}


#endif /* INCLUDE_CORE_MODELS_STANDARDSTUDENT_HPP_ */
