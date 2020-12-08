#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include <boost/log/trivial.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/common.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/exceptions.hpp>
//#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/console.hpp>

#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>


namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace attrs = boost::log::attributes;


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

std::ostream& operator<< (std::ostream& os, const LogType type) {
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

BOOST_LOG_ATTRIBUTE_KEYWORD(log_type, "log_type", LogType);

class Logger {
public:
    Logger() {

        fs::path filepath(fs::current_path());
        filepath /= "logs";

        //boost::log::add_file_log("sample.log");

        boost::log::register_simple_formatter_factory<
            boost::log::trivial::severity_level, char >("log_type");

        logging::add_file_log
        (
            keywords::file_name = "sample_%N.log",
            keywords::rotation_size = 10 * 1024 * 1024,
            keywords::target = filepath.string(),
            keywords::format = "[Thread:%ThreadID%][%TimeStamp%][%Severity%][%log_type%]: %Message%"
        );

        logging::add_console_log(std::cout, 
            keywords::format = "[Thread:%ThreadID%][%TimeStamp%][%Severity%][%log_type%]: %Message%"
        );

        logging::core::get()->set_filter
        (
            logging::trivial::severity >= logging::trivial::debug
        );

        logging::add_common_attributes();
        logging::core::get()->add_global_attribute("log_type", logtype);
       // BOOST_LOG_TRIVIAL(trace) << "logtype created and registered";
    }
	void log(const std::string &message, const LogSeverity severity = LogSeverity::Debug, const LogType type = LogType::General) {
        switch (severity) {
        case LogSeverity::Trace:
            BOOST_LOG_TRIVIAL(trace) << message;
            break;
        case LogSeverity::Debug:
            BOOST_LOG_TRIVIAL(debug) << message;
            break;
        case LogSeverity::Info:
            BOOST_LOG_TRIVIAL(info) << message;
            break;
        case LogSeverity::Warning:
            BOOST_LOG_TRIVIAL(warning) << message;
            break;
        case LogSeverity::Error:
            BOOST_LOG_TRIVIAL(error) << message;
            break;
        case LogSeverity::Fatal:
            BOOST_LOG_TRIVIAL(fatal) << message;
            break;
        }
	}
private:
    //src::severity_logger< severity_level > slg;
    //src::severity_logger_mt<LogSeverity> slg;
    attrs::mutable_constant<LogType> logtype = attrs::mutable_constant<LogType>(LogType::General);
};

static inline Logger logInstance = Logger();