#include "Logger.h"
#include <spdlog\sinks\stdout_color_sinks.h>
#include <spdlog\sinks\basic_file_sink.h>

using namespace ic;

std::shared_ptr<StandardLogger> Logger::logger;

void Logger::start() {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::trace);

    console_sink->set_pattern("[console][%^%=8l%$] %v");

    fs::path filepath(fs::current_path());
    filepath /= "logs";
    filepath /= "latest.txt";

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(filepath.string(), true);
    file_sink->set_pattern("[%Y-%m-%d : %H:%M:%S][thread %t][%^%l%$] %v");
    file_sink->set_level(spdlog::level::debug);

    auto loggerbackend = spdlog::logger("cout_file", { console_sink, file_sink });
    
    //trace -> debug -> info
    loggerbackend.set_level(spdlog::level::trace);

    Logger::logger = std::make_unique<StandardLogger>(loggerbackend);

    Logger::info("Logger starting up.");
}

void Logger::stop() {
    Logger::info("Logger shutting down.");
    spdlog::shutdown();
    logger.reset();
}

//#undef IC_LOGGER_LEVEL