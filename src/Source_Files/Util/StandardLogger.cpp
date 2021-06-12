#include "include.h"
#include "StandardLogger.h"

#include <iostream>
#include <ostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace ic;

StandardLogger::StandardLogger() {

}
StandardLogger::~StandardLogger() {}

void StandardLogger::log(const std::string& message, const LogSeverity severity, const LogType type) {
	std::cout << message;
}