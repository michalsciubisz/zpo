#ifndef INCLUDE_CORE_REPOSITORIES_IUNIVERSITYREPOSITORY_HPP_
#define INCLUDE_CORE_REPOSITORIES_IUNIVERSITYREPOSITORY_HPP_

#include "University.hpp"

namespace SystemCore {
    class IUniversityRepository {
    public:
        virtual SystemCore::University& get_by_id(SystemCore::UniversityID university_id) = 0;
    };
}


#endif /* INCLUDE_CORE_REPOSITORIES_IUNIVERSITYREPOSITORY_HPP_ */
