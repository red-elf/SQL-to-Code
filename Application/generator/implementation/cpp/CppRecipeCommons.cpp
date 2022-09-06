//
// Created by milosvasic on 01.09.22.
//

#include "CppRecipeCommons.h"

std::string CppRecipeCommons::getClassName(std::shared_ptr<ClassNameIngredient> &ingredient) {

    return ingredient->getName();
}