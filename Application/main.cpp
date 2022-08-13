#include <chrono>
#include <string>
#include <iostream>
#include <argparse/argparse.hpp>

#include "Logger.h"
#include "LogLevel.h"
#include "LoggerSimple.h"
#include "LoggerChained.h"
#include "VersionInfo.h"
#include "FileOutputWriter.h"

namespace Utils {

    static Logger *createLogger() {

        static LoggerSimple simpleLogger;
        return &simpleLogger;
    }
}

int main() {

    auto logger = Utils::createLogger();

    logger->log("ddl2code", "Hello!");

    return 0;
}