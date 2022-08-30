//
// Created by milosvasic on 29.08.22.
//

#include "Utils.h"
#include "CodeGenerator.h"

#include "algorithm"

using namespace Utils;

bool CodeGenerator::feed(Ingredients *items) {

    size_t size = ingredients.size();
    ingredients.push_back(items);
    return size != ingredients.size();
}

bool CodeGenerator::doRegister(IRecipe *what) {

    size_t size = recipes.size();
    recipes.push_back(what);
    return size != recipes.size();
}

bool CodeGenerator::doUnregister(IRecipe *&what) {

    size_t size = recipes.size();
    recipes.erase(std::remove(recipes.begin(), recipes.end(), what), recipes.end());
    return size != recipes.size();
}

bool CodeGenerator::execute() {

    const std::string tag = "code generator :: execute";

    if (ingredients.empty()) {

        w(tag, "No ingredients added");

        return false;

    } else {

        v(tag, "Ingredients added: " + std::to_string(ingredients.size()));
    }

    if (recipes.empty()) {

        w(tag, "No recipes registered");

        return false;
    }

    for (IRecipe *recipe: recipes) {

        v(tag, recipe->getDescription());

        if (!recipe->cook(ingredients)) {

            e(tag, recipe->getDescription() + ": failed");
            return false;
        }
    }
    return true;
}