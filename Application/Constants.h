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

    std::string TAB = "    ";
    std::string BLOCK_ON = "{";
    std::string BLOCK_OFF = "}";
    std::string COMMENT_ON = "/*";
    std::string COMMENT_OFF = "*/";

    std::string SIGNATURE = "Generated with '" + std::string(VERSIONABLE_NAME) + "' " + getVersion()
                            + lineBreak() + TAB + getHomepage();
}

#endif //_CONSTANTS_H
