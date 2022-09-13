//
// Created by milosvasic on 01.09.22.
//

#include "CppRecipeCommons.h"

#include "string"
#include "algorithm"
#include "Commons.h"
#include "../ClassPropertyDataType.h"

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

std::string CppRecipeCommons::getPropertyType(std::shared_ptr<ClassPropertyIngredient> &ingredient) {

    auto type = ingredient->getType();
    switch (type) {

        case ClassPropertyDataType::INT:
            return "int";
        case ClassPropertyDataType::SMALLINT:
            return "short";
        case ClassPropertyDataType::LONG:
        case ClassPropertyDataType::BIGINT:
            return "long";
        case ClassPropertyDataType::FLOAT:
            return "float";
        case ClassPropertyDataType::DOUBLE:
        case ClassPropertyDataType::DECIMAL:
        case ClassPropertyDataType::REAL:
            return "double";
        case ClassPropertyDataType::BOOLEAN:
            return "bool";
        case ClassPropertyDataType::CHAR:
            return "char";
        case ClassPropertyDataType::STRING:
        case ClassPropertyDataType::VARCHAR:
            return "std::string";
        case ClassPropertyDataType::TIME:
        case ClassPropertyDataType::DATE:
        case ClassPropertyDataType::DATETIME:
            return "long";
        default:
            return "";
    }
}