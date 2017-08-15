#include "simulator.h"
#include <plog/Log.h>
#include <plog/Appenders/ColorConsoleAppender.h>

Simulator::Simulator() {
    static plog::ColorConsoleAppender<plog::TxtFormatter> appender;
    plog::init(plog::debug, &appender);

    LOG_VERBOSE << "This is a VERBOSE message";
    LOG_DEBUG << "This is a DEBUG message";
    LOG_INFO << "This is an INFO message";
    LOG_WARNING << "This is a WARNING message";
    LOG_ERROR << "This is an ERROR message";
    LOG_FATAL << "This is a FATAL message";
}
