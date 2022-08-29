//
// Created by milosvasic on 29.08.22.
//

#include "ClassPropertyIngredient.h"

ClassPropertyIngredient::ClassPropertyIngredient(std::string &name, ClassPropertyDataType &type) : type(type) {

    this->name = name;
}

ClassPropertyDataType &ClassPropertyIngredient::getType() {

    return this->type;
}

std::string ClassPropertyIngredient::getName() {

    return this->name;
}
