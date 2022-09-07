//
// Created by milosvasic on 07.09.22.
//

#ifndef _TARGET_H
#define _TARGET_H

#include "string"

namespace Target {

    std::string CPP = "cpp";
    std::string JVM = "jvm";
    std::string DART = "dart";

    enum class ETarget {

        CPP,
        JVM,
        DART,
        UNKNOWN
    };
}

#endif //_TARGET_H
