#ifndef INCLUDE_REPOSITORIES_UNIVERSITYREPOSITORY_HPP_
#define INCLUDE_REPOSITORIES_UNIVERSITYREPOSITORY_HPP_

#include "University.hpp"
#include "NotImplementedException.hpp"

namespace SystemInfrastructure {
    class UniversityRepository : public SystemCore::IUniversityRepository {
    public:
        SystemCore::University& get_by_id(SystemCore::UniversityID universityId) override {
            throw SystemCore::NotImplementedException();
        }
    };
}

#endif /* INCLUDE_REPOSITORIES_UNIVERSITYREPOSITORY_HPP_ */
