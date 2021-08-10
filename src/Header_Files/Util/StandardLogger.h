#pragma once
#include <spdlog\spdlog.h>

namespace ic {
    class StandardLogger {
    public:
        StandardLogger(spdlog::logger& loggerbackend) : loggerbackend(loggerbackend) {

        }

        spdlog::logger loggerbackend;
    };
}
