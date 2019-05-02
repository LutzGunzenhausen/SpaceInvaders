#ifndef LOGGINGSERVICE_H_INCLUDED
#define LOGGINGSERVICE_H_INCLUDED

#include <string>

namespace Game {

class LoggingService {
public:
    virtual void log(const std::string &message) = 0;
};
}

#endif // LOGGINGSERVICE_H_INCLUDED
