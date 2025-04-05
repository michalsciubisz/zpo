#ifndef INCLUDE_CORE_SERVICES_STUDENTWRITERSERVICE_HPP_
#define INCLUDE_CORE_SERVICES_STUDENTWRITERSERVICE_HPP_

#include <memory>
#include <sstream>

#include "IStudentWriterService.hpp"
#include "IStudentRepository.hpp"
#include "IUniversityRepository.hpp"
#include "ILogger.hpp"
#include "IStudentFactory.hpp"
#include "DomainException.hpp"

namespace SystemInfrastructure {
    class StudentWriterService : public SystemCore::IStudentWriterService {
    private:
        SystemCore::IStudentRepository* student_repository_;
        SystemCore::IUniversityRepository* university_repository_;
        SystemCore::ILogger* logger_;
        SystemCore::IStudentFactory* student_factory_;

    public:
        StudentWriterService(
                SystemCore::IStudentRepository* student_repository,
                SystemCore::IUniversityRepository* university_repository,
                SystemCore::ILogger* logger,
                SystemCore::IStudentFactory* student_factory) : student_repository_(student_repository),
                                                                university_repository_(university_repository),
                                                                logger_(logger),
                                                                student_factory_(student_factory) {
        }

        void add(std::string email_address, SystemCore::UniversityID university_id) override {
            std::ostringstream oss;

            oss << "Log: End add student with email " << email_address;
            logger_->log(oss.str());

            if (student_repository_->exists(email_address)) {
                throw SystemCore::DomainException(
                        "A user with the same e-mail address already exists.");
            }

            SystemCore::University university = university_repository_->get_by_id(
                    university_id);

            std::unique_ptr<SystemCore::Student> student = student_factory_->create(email_address,
                                                                                    university_id,
                                                                                    university.get_package_type());
            student_repository_->add(std::move(student));

            oss.clear();
            oss.str("");
            oss << "Log: End add student with email " << email_address;
            logger_->log(oss.str());
        }

        void add_bonus_allowances() override {
            auto students = student_repository_->get_students_for_allowance_increase();
            for (SystemCore::LimitedStudent* s : students) {
                s->add_bonus_allowance();
            }
        }
    };
}

#endif /* INCLUDE_CORE_SERVICES_STUDENTWRITERSERVICE_HPP_ */
