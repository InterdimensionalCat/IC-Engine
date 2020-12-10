#pragma once
#include "Logger.h"


class LoggerProvider {
public:
	static void log(const std::string& message, const LogSeverity severity = LogSeverity::Debug, const LogType type = LogType::General) {
		if (!logger) {
			logger = std::make_unique<Logger>();
		}

		logger->log(message, severity, type);
	}

private:
	inline static std::unique_ptr<Logger> logger;
};