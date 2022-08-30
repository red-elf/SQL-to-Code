//
// Created by milosvasic on 29.08.22.
//

#include "IRecipe.h"

#include <utility>

IRecipe::IRecipe(std::string description) {

    this->description = std::move(description);
}

std::string IRecipe::getDescription() {

    return this->description;
}