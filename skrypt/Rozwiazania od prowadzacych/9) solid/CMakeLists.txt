cmake_minimum_required(VERSION 3.13)
project(solid_refactoring_refactored)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(include/core)
include_directories(include/core/exceptions)
include_directories(include/core/factories)
include_directories(include/core/models)
include_directories(include/core/repositories)
include_directories(include/core/services)
include_directories(include/infrastructure/repositories)
include_directories(include/infrastructure/services)

add_executable(solid_refactoring_refactored
        include/core/exceptions/DomainException.hpp
        include/core/exceptions/NotImplementedException.hpp
        include/core/factories/IStudentFactory.hpp
        include/core/factories/StudentFactory.hpp
        include/core/models/IBonusAllowable.hpp
        include/core/models/LimitedStudent.hpp
        include/core/models/PackageType.hpp
        include/core/models/PremiumStudent.hpp
        include/core/models/StandardStudent.hpp
        include/core/models/Student.hpp
        include/core/models/University.hpp
        include/core/models/UnlimitedStudent.hpp
        include/core/repositories/IStudentRepository.hpp
        include/core/repositories/IUniversityRepository.hpp
        include/core/services/ILogger.hpp
        include/core/services/IStudentReaderService.hpp
        include/core/services/IStudentWriterService.hpp
        include/infrastructure/repositories/StudentRepository.hpp
        include/infrastructure/repositories/UniversityRepository.hpp
        include/infrastructure/services/ConsoleLogger.hpp
        include/infrastructure/services/StudentReaderService.hpp
        include/infrastructure/services/StudentWriterService.hpp
        src/program.cpp)
