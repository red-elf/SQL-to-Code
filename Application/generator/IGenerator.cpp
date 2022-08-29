//
// Created by milosvasic on 29.08.22.
//

#include "IGenerator.h"

#include "algorithm"

bool IGenerator::feed(IIngredient *ingredient) {

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