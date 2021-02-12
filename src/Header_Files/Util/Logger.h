#pragma once
#include <string>

namespace ic {
    enum class LogSeverity {
        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Fatal
    };

    enum class LogType {
        General,
        Input,
        Physics,
        Ai,
        Rendering,
        Audio
    };

    class Logger {
    public:
        Logger() {}
        virtual ~Logger() {}
        virtual void log(const std::string& message, const LogSeverity severity = LogSeverity::Debug, const LogType type = LogType::General) = 0;
    };
}