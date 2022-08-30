//
// Created by milosvasic on 29.08.22.
//

#include "IRecipe.h"

IRecipe::IRecipe(std::string description) {

    this->description = description;
}

std::string IRecipe::getDescription() {

    return this->description;
}