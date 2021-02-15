#pragma once
#include "Logger.h"
#include <ostream>
#include <string>
#include <iostream>


namespace ic {
    class StandardLogger : public Logger {
    public:
        StandardLogger();
        ~StandardLogger() override;
        void log(const std::string& message, const LogSeverity severity = LogSeverity::Debug, const LogType type = LogType::General) override;
    private:
        friend std::ostream& operator<< (std::ostream& os, const LogType type) {
            switch (type) {
            case(LogType::General):
                os << "General";
                break;
            case(LogType::Input):
                os << "Input";
                break;
            case(LogType::Physics):
                os << "Physics";
                break;
            case(LogType::Ai):
                os << "Ai";
                break;
            case(LogType::Rendering):
                os << "Rendering";
                break;
            case(LogType::Audio):
                os << "Audio";
                break;
            }

            return os;
        }

        std::string logTypeToString(const LogType type) {
            switch (type) {
            case(LogType::General):
                return "General";
                break;
            case(LogType::Input):
                return "Input";
                break;
            case(LogType::Physics):
                return "Physics";
                break;
            case(LogType::Ai):
                return "Ai";
                break;
            case(LogType::Rendering):
                return "Rendering";
                break;
            case(LogType::Audio):
                return "Audio";
                break;
            }

            return "General";
        }
    };
}