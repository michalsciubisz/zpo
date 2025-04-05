#ifndef INCLUDE_CORE_MODELS_STUDENT_HPP_
#define INCLUDE_CORE_MODELS_STUDENT_HPP_

#include <string>

namespace SystemCore {
    //OCP
    class Student {

    private:
        std::string email_address_;
        int university_id_;
        int monthly_ebook_allowance_ = STANDARD_ALLOWANCE;
        int currently_borrowed_ebooks_ = 0;

    protected:
        const static int STANDARD_ALLOWANCE = 10;

        Student(std::string email_address, int university_id) :
                email_address_(email_address), university_id_(university_id) {
        }

        void set_monthly_ebook_allowance(int new_limit) {
            monthly_ebook_allowance_ = new_limit;
        }

    public:
        std::string get_email_address() {
            return email_address_;
        }

        int get_university_id() {
            return university_id_;
        }

        int get_monthly_ebook_allowance() {
            return monthly_ebook_allowance_;
        }

        int get_currently_borrowed_ebooks() {
            return currently_borrowed_ebooks_;
        }
    };
}

#endif /* INCLUDE_CORE_MODELS_STUDENT_HPP_ */
