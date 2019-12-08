#include "MessageSystem.h"
#include <iostream>

MessageSystem::MessageSystem()
{

}

void MessageSystem::logNormalMessage(std::string message)
{
    std::cout << message << std::endl;
}

void MessageSystem::logWarningMessage(std::string message)
{
    std::cout << message << std::endl;
}

void MessageSystem::logErrorMessage(std::string message)
{
    std::cout << message << std::endl;
}

void MessageSystem::logCriticalErrorMessage(std::string message)
{
    std::cout << message << std::endl;
    int *num = 0;
    *num;
}
