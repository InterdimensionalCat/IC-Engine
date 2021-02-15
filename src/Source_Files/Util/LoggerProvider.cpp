#include "LoggerProvider.h"
#include "StandardLogger.h" 

using namespace ic;

void LoggerProvider::log(const std::string& message, const LogSeverity severity, const LogType type) {
	if (!logger) {
		logger = std::make_unique<StandardLogger>();
	}

	logger->log(message, severity, type);
}

void LoggerProvider::logAndThrowLogicError(const std::string& message, const LogSeverity severity, const LogType type) {
	log(message, severity, type);
	throw std::logic_error(message);
}