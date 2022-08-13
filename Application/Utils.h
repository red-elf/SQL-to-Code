//
// Created by milosvasic on 13.08.22.
//

#ifndef _UTILS_H
#define _UTILS_H

#include "Logger.h"
#include "LoggerSimple.h"
#include "BuildConfig.h"
#include "VersionInfo.h"

namespace Utils {

    static Logger *getLogger() {

        static LoggerSimple simpleLogger;
        return &simpleLogger;
    }

    static void log(const std::string &tag, const std::string &message, const LogLevel &level) {

        auto logger = getLogger();

        auto time = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::system_clock::now().time_since_epoch()).count();

        logger->logFull(
                VERSIONABLE_NAME,
                getVersion(),
                time,
                level,
                tag,
                message,
                std::list<std::string>()
        );
    }

    static void v(const std::string &tag, const std::string &message) {

        auto level = LogLevel::verbose;
        log(tag, message, level);
    }

    static void d(const std::string &tag, const std::string &message) {

        auto level = LogLevel::debug;
        log(tag, message, level);
    }

    static void i(const std::string &tag, const std::string &message) {

        auto level = LogLevel::info;
        log(tag, message, level);
    }

    static void w(const std::string &tag, const std::string &message) {

        auto level = LogLevel::warning;
        log(tag, message, level);
    }

    static void e(const std::string &tag, const std::string &message) {

        auto level = LogLevel::error;
        log(tag, message, level);
    }
}

#endif //_UTILS_H
