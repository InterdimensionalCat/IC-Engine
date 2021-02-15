#pragma once
#include "Logger.h"
#include <memory>
#include <string>

namespace ic {
	class LoggerProvider {
	public:
		static void log(const std::string& message, const LogSeverity severity = LogSeverity::Debug, const LogType type = LogType::General);
		static void logAndThrowLogicError(const std::string& message, const LogSeverity severity = LogSeverity::Fatal, const LogType type = LogType::General);
	private:
		inline static std::unique_ptr<Logger> logger;
	};
}
