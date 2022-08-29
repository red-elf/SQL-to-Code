//
// Created by milosvasic on 29.08.22.
//

#include "ClassNameIngredient.h"

ClassNameIngredient::ClassNameIngredient(std::string &name) {

    this->name = name;
}

std::string ClassNameIngredient::getName() {

    return this->name;
}