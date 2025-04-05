#include <memory>

#include "IStudentRepository.hpp"
#include "IUniversityRepository.hpp"
#include "StudentRepository.hpp"
#include "UniversityRepository.hpp"

#include "IStudentWriterService.hpp"
#include "StudentWriterService.hpp"

#include "ILogger.hpp"
#include "ConsoleLogger.hpp"

#include "IStudentFactory.hpp"
#include "StudentFactory.hpp"

int main() {
    std::unique_ptr<SystemCore::IStudentRepository> student_repository(
            std::make_unique<SystemInfrastructure::StudentRepository>());
    std::unique_ptr<SystemCore::IUniversityRepository> university_repository(
            std::make_unique<SystemInfrastructure::UniversityRepository>());
    std::unique_ptr<SystemCore::ILogger> logger(std::make_unique<SystemInfrastructure::ConsoleLogger>());
    std::unique_ptr<SystemCore::IStudentFactory> student_factory(
            std::make_unique<SystemCore::StudentFactory>());

    std::unique_ptr<SystemCore::IStudentWriterService> student_writer_service(
            std::make_unique<SystemInfrastructure::StudentWriterService>(student_repository.get(),
                                                                         university_repository.get(),
                                                                         logger.get(),
                                                                         student_factory.get()));

    return 0;
}
