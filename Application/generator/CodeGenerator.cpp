//
// Created by milosvasic on 29.08.22.
//

#include "CodeGenerator.h"

#include "algorithm"

bool CodeGenerator::feed(Ingredients *items) {

    if (std::find(ingredients.begin(), ingredients.end(), items) != ingredients.end()) {

        return true;

    } else {

        ingredients.push_back(items);

        if (std::find(ingredients.begin(), ingredients.end(), items) != ingredients.end()) {

            return true;
        }
    }
    return false;
}

bool CodeGenerator::doRegister(IRecipe *what) {

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

bool CodeGenerator::doUnregister(IRecipe *&what) {

    if (std::find(recipes.begin(), recipes.end(), what) != recipes.end()) {

        recipes.erase(find(recipes.begin(), recipes.end(), what));

        if (std::find(recipes.begin(), recipes.end(), what) != recipes.end()) {

            return false;
        }
    }
    return true;
}

bool CodeGenerator::execute() {

    for (IRecipe *recipe: recipes) {

        if (!recipe->cook(ingredients)) {

            return false;
        }
    }
    return true;
}