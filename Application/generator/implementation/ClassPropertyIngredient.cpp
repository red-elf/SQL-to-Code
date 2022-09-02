//
// Created by milosvasic on 29.08.22.
//

#include "ClassPropertyIngredient.h"

ClassPropertyDataType &ClassPropertyIngredient::getType() {

    return this->type;
}

std::string ClassPropertyIngredient::getName() {

    return this->name;
}

IngredientType ClassPropertyIngredient::getIngredientType() {

    return IngredientType::CLASS_PROPERTY;
}
