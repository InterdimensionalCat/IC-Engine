#include "include.h"
#include "StandardLogger.h"

#include <iostream>
#include <ostream>
#include <string>
#include <sstream>
#include <boost/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/common.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/exceptions.hpp>
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
#include <boost/date_time/local_time/local_time.hpp>
#include <iostream>


namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace attrs = boost::log::attributes;

using namespace ic;

StandardLogger::StandardLogger() {

    fs::path filepath(fs::current_path());
    filepath /= "logs";

    boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();
    boost::gregorian::date dateObj = timeLocal.date();

    std::ostringstream oss;
    oss << dateObj;

    logging::add_file_log
    (
        //keywords::file_name = "sample_%N.log",
        keywords::file_name = oss.str() + "_%N.log",
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::target = filepath.string(),
        keywords::format = "[Thread:%ThreadID%][%TimeStamp%][%Severity%]%Message%"
    );

    logging::add_console_log(std::cout,
        keywords::format = "[Thread:%ThreadID%][%TimeStamp%][%Severity%]%Message%"
    );

    //logging::core::get()->set_filter
    //(
    //    logging::trivial::severity >= logging::trivial::debug
    //);

    logging::add_common_attributes();
}
StandardLogger::~StandardLogger() {}
void StandardLogger::log(const std::string& message, const LogSeverity severity, const LogType type) {
    //std::ostringstream oss;
    //oss << "[" << type << "]: " << message;
    switch (severity) {
    case LogSeverity::Trace:
        BOOST_LOG_TRIVIAL(trace) << "[" << type << "]: " << message;
        break;
    case LogSeverity::Debug:
        BOOST_LOG_TRIVIAL(debug) << "[" << type << "]: " << message;
        break;
    case LogSeverity::Info:
        BOOST_LOG_TRIVIAL(info) << "[" << type << "]: " << message;
        break;
    case LogSeverity::Warning:
        BOOST_LOG_TRIVIAL(warning) << "[" << type << "]: " << message;
        break;
    case LogSeverity::Error:
        BOOST_LOG_TRIVIAL(error) << "[" << type << "]: " << message;
        break;
    case LogSeverity::Fatal:
        BOOST_LOG_TRIVIAL(fatal) << "[" << type << "]: " << message;
        break;
    }
}