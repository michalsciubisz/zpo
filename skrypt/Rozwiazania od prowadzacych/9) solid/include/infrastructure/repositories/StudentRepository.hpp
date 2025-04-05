#ifndef INCLUDE_REPOSITORIES_STUDENTREPOSITORY_HPP_
#define INCLUDE_REPOSITORIES_STUDENTREPOSITORY_HPP_

#include <vector>
#include <string>

#include "IStudentRepository.hpp"
#include "NotImplementedException.hpp"

namespace SystemInfrastructure {
    class StudentRepository : public SystemCore::IStudentRepository {
    public:
        void add(std::unique_ptr<SystemCore::Student> student) override {
            throw SystemCore::NotImplementedException();
        }
        bool exists(std::string email_address) const override {
            throw SystemCore::NotImplementedException();
        }

        std::vector<SystemCore::LimitedStudent*> get_students_for_allowance_increase() override {
            throw SystemCore::NotImplementedException();
        }
    };
}

#endif /* INCLUDE_REPOSITORIES_STUDENTREPOSITORY_HPP_ */
