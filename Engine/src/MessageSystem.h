#ifndef MESSAGESYSTEM_H
#define MESSAGESYSTEM_H
#include <string>

class MessageSystem
{
public:
    MessageSystem();
    void logNormalMessage(std::string message);
    void logWarningMessage(std::string message);
    void logErrorMessage(std::string message);
    void logCriticalErrorMessage(std::string message);///< A critical error message will end the program.
};

#endif // MESSAGESYSTEM_H
