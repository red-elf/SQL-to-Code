//
// Created by milosvasic on 13.08.22.
//

#ifndef _UTILS_H
#define _UTILS_H

#include "Logger.h"
#include "LoggerSimple.h"
#include "BuildConfig.h"
#include "VersionInfo.h"
#include "sql/SQLStatement.h"

using namespace hsql;

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

    std::string getDataType(DataType &dataType) {

        switch (dataType) {
            case DataType::BOOLEAN:
                return "Boolean";
            case DataType::CHAR:
                return "Char";
            case DataType::DATE:
            case DataType::TIME:
            case DataType::DATETIME:
            case DataType::BIGINT:
            case DataType::LONG:
                return "Long";
            case DataType::FLOAT:
                return "Float";
            case DataType::DOUBLE:
            case DataType::REAL:
            case DataType::DECIMAL:
                return "Double";
            case DataType::INT:
            case DataType::SMALLINT:
                return "Integer";
            case DataType::TEXT:
            case DataType::VARCHAR:
                return "String";
            default:
                throw std::invalid_argument("Unable to determine the data type");
        }
    }
}

#endif //_UTILS_H
