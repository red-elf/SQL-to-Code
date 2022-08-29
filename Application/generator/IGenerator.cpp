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

bool IGenerator::doRegister(IRecipe *what) {

    if (std::find(recipes.begin(), recipes.end(), what) != recipes.end()) {

        return true;

    } else {

        recipes.push_back(what);

        if (std::find(recipes.begin(), recipes.end(), what) != recipes.end()) {

            return true;
        }
    }
    return false;
}

bool IGenerator::doUnregister(IRecipe *&what) {

    if (std::find(recipes.begin(), recipes.end(), what) != recipes.end()) {

        recipes.erase(find(recipes.begin(), recipes.end(), what));

        if (std::find(recipes.begin(), recipes.end(), what) != recipes.end()) {

            return false;
        }
    }
    return true;
}

bool IGenerator::execute() {

    for (IRecipe *recipe: recipes) {

        if (!recipe->cook(ingredients)) {

            return false;
        }
    }
    return true;
}