//
// Created by milosvasic on 01.09.22.
//

#include "CppRecipeCommons.h"

#include "string"
#include "algorithm"
#include "Commons.h"

using namespace Commons::Strings;

CppRecipeCommons::CppRecipeCommons(std::string &dest) {

    this->destination = dest;
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