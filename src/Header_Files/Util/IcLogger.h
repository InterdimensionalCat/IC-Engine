#pragma once
#include <string>
#include "StandardLogger.h"

#ifndef IC_LOGGER_LEVEL
#define IC_LOGGER_LEVEL(level) \
template<typename... Args>\
static void level(auto fmt, Args&&... args) {\
    logger->loggerbackend.level(fmt, args...);\
}\
static void level(auto fmt) {\
    logger->loggerbackend.level(fmt);\
}
#endif

namespace ic {

    class StandardLogger;

    class Logger {
    public:
        static void start();
        static void stop();


        IC_LOGGER_LEVEL(info);
        IC_LOGGER_LEVEL(trace);
        IC_LOGGER_LEVEL(debug);
        IC_LOGGER_LEVEL(warn);
        IC_LOGGER_LEVEL(error);
        IC_LOGGER_LEVEL(critical);


    private:
        static std::shared_ptr<StandardLogger> logger;
    };
}

#undef IC_LOGGER_LEVEL