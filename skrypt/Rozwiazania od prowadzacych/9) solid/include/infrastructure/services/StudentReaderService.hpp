#ifndef INCLUDE_CORE_SERVICES_STUDENTREADERSERVICE_HPP_
#define INCLUDE_CORE_SERVICES_STUDENTREADERSERVICE_HPP_

#include <vector>

#include "IStudentReaderService.hpp"
#include "NotImplementedException.hpp"

namespace SystemCore {
    class StudentReaderService : public SystemCore::IStudentReaderService {
        //...
    public:
        std::vector<SystemCore::Student*> get_students_by_university() override {
            //...
            throw SystemCore::NotImplementedException();
        }

        std::vector<SystemCore::Student*> get_students_by_currently_borrowed_ebooks() override {
            //...
            throw SystemCore::NotImplementedException();
        }
    };
}

#endif /* INCLUDE_CORE_SERVICES_STUDENTREADERSERVICE_HPP_ */
