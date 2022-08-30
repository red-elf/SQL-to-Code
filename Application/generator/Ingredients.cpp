//
// Created by milosvasic on 29.08.22.
//

#include "Ingredients.h"

#include "algorithm"

Ingredients::Ingredients(std::string &description) {

    this->description = description;
}

std::string Ingredients::getDescription() {

    return this->description;
}

bool Ingredients::add(IIngredient *ingredient) {

    if (std::find(ingredients.begin(), ingredients.end(), ingredient) != ingredients.end()) {

        return true;

    } else {

        ingredients.push_back(ingredient);

        if (std::find(ingredients.begin(), ingredients.end(), ingredient) != ingredients.end()) {

            return true;
        }
    }
    return false;
}