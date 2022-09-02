//
// Created by milosvasic on 29.08.22.
//

#include "ClassNameIngredient.h"

std::string ClassNameIngredient::getName() {

    return this->name;
}

IngredientType ClassNameIngredient::getIngredientType() {

    return IngredientType::CLASS_NAME;
}
