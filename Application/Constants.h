//
// Created by milosvasic on 07.09.22.
//

#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include "string"
#include "Commons.h"
#include "BuildConfig.h"
#include "VersionInfo.h"

using namespace Commons::Strings;

namespace Constants {

    const std::string CLASS = "class";
    const std::string STATEMENT_END = ";";

    const std::string TAB = "    ";
    const std::string BLOCK_ON = "{";
    const std::string BLOCK_OFF = "}";
    const std::string METHOD_ON = "(";
    const std::string METHOD_OFF = ")";
    const std::string COMMENT_ON = "/*";
    const std::string COMMENT_OFF = "*/";

    const std::string SIGNATURE = "Generated with '" + std::string(VERSIONABLE_NAME) + "' " + getVersion()
                            + lineBreak() + TAB + getHomepage();
}

#endif //_CONSTANTS_H
