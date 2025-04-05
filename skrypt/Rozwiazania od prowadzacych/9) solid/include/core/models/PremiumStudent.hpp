#ifndef INCLUDE_CORE_MODELS_PREMIUMSTUDENT_HPP_
#define INCLUDE_CORE_MODELS_PREMIUMSTUDENT_HPP_

#include <string>

#include "LimitedStudent.hpp"

namespace SystemCore {
    class PremiumStudent : public LimitedStudent {
    public:
        PremiumStudent(std::string email_address, int university_id) :
                LimitedStudent(email_address, university_id) {
            set_monthly_ebook_allowance(Student::STANDARD_ALLOWANCE * 2);
        }

        void add_bonus_allowance() override {
            set_monthly_ebook_allowance(get_monthly_ebook_allowance() + 10);
        }
    };
}

#endif /* INCLUDE_CORE_MODELS_PREMIUMSTUDENT_HPP_ */
