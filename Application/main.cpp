#include <iostream>
#include <chrono>

#include "Logger.h"
#include "LogLevel.h"
#include "LoggerSimple.h"
#include "LoggerFactory.h"
#include "LoggerLibrary.h"

namespace Utils {

    static Logger *createSimpleLogger() {

        static LoggerSimple loggerSimple;
        return &loggerSimple;
    }
}

int main() {

    auto logger = Utils::createSimpleLogger();

    logger->log("ddl2code", "Hello!");

    return 0;
}