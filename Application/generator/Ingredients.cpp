//
// Created by milosvasic on 29.08.22.
//

#include "Ingredients.h"

#include "algorithm"

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