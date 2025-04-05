#ifndef INCLUDE_CORE_FACTORIES_STUDENTFACTORY_HPP_
#define INCLUDE_CORE_FACTORIES_STUDENTFACTORY_HPP_

#include <memory>
#include <string>

#include "IStudentFactory.hpp"
#include "Student.hpp"
#include "PackageType.hpp"
#include "StandardStudent.hpp"
#include "PremiumStudent.hpp"
#include "UnlimitedStudent.hpp"

namespace SystemCore {
    class StudentFactory : public IStudentFactory {
    public:
        std::unique_ptr<SystemCore::Student> create(std::string email_address, int university_id,
                                                    SystemCore::PackageType package_type) override {
            switch (package_type) {
                case SystemCore::PackageType::Standard:
                    return std::make_unique<StandardStudent>(email_address, university_id);
                case SystemCore::PackageType::Premium:
                    return std::make_unique<PremiumStudent>(email_address, university_id);
                case SystemCore::PackageType::Unlimited:
                    return std::make_unique<UnlimitedStudent>(email_address, university_id);
                default:
                    throw "There is no associated student for this package";
            }
        }
    };
}

#endif /* INCLUDE_CORE_FACTORIES_STUDENTFACTORY_HPP_ */
