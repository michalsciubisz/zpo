#ifndef INCLUDE_CORE_MODELS_UNIVERSITY_HPP_
#define INCLUDE_CORE_MODELS_UNIVERSITY_HPP_

#include <string>

#include "PackageType.hpp"

namespace SystemCore {
    using UniversityID = int;

    class University {
    private:
        SystemCore::UniversityID id_;
        std::string name_;
        SystemCore::PackageType package_type_;
    public:
        University(SystemCore::UniversityID id, std::string name,
                   SystemCore::PackageType package_type) :
                id_(id), name_(name), package_type_(package_type) {
        }
        PackageType get_package_type() {
            return package_type_;
        }
    };
}


#endif /* INCLUDE_CORE_MODELS_UNIVERSITY_HPP_ */
