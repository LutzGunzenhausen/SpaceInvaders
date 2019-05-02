#ifndef NULLLOGGINGSERVICE_HPP_INCLUDED
#define NULLLOGGINGSERVICE_HPP_INCLUDED

#include <string>
#include "Common/Logging/LoggingService.h"

namespace Game {

class NullLoggingService : public LoggingService {
public:
    void log(const std::string &message) {
    }
};
}

#endif // NULLLOGGINGSERVICE_HPP_INCLUDED
