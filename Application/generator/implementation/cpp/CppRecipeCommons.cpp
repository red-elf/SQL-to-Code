//
// Created by milosvasic on 01.09.22.
//

#include "CppRecipeCommons.h"

#include "string"
#include "algorithm"

std::string capitalize(std::string &what){

    what[0] = toupper(what[0]);
    return what;
}

std::string deCapitalize(std::string &what){

    what[0] = tolower(what[0]);
    return what;
}

std::string camelcase(std::string &what) {

    auto n = what.length();

    int res_ind = 0;

    for (int i = 0; i < n; i++) {

        // check for spaces in the sentence
        if (what[i] == ' ') {

            what[i + 1] = toupper(what[i + 1]);
            continue;

        } else {

            what[res_ind++] = what[i];
        }
    }

    return what.substr(0, res_ind);
}

std::string CppRecipeCommons::getClassName(std::shared_ptr<ClassNameIngredient> &ingredient) {

    auto what = ingredient->getName();
    std::replace(what.begin(), what.end(), '_', ' ');
    what = camelcase(what);
    return capitalize(what);
}

std::string CppRecipeCommons::getPropertyName(std::shared_ptr<ClassPropertyIngredient> &ingredient) {

    auto what = ingredient->getName();
    std::replace(what.begin(), what.end(), '_', ' ');
    what = camelcase(what);
    return deCapitalize(what);
}