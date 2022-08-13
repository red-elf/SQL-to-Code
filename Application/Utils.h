//
// Created by milosvasic on 13.08.22.
//

#ifndef _UTILS_H
#define _UTILS_H

#include "Logger.h"
#include "LoggerSimple.h"

namespace Utils {

    static Logger *createLogger() {

        static LoggerSimple simpleLogger;
        return &simpleLogger;
    }
}

#endif //_UTILS_H
