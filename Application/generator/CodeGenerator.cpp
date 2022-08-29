//
// Created by milosvasic on 29.08.22.
//

#include "CodeGenerator.h"

#include "algorithm"
#include "Utils.h"

using namespace Utils;

bool CodeGenerator::feed(Ingredients *items) {

    const std::string tag = "code generator :: feed";

    if (std::find(ingredients.begin(), ingredients.end(), items) != ingredients.end()) {

        w(tag, "Already fed");

        return true;

    } else {

        ingredients.push_back(items);

        if (std::find(ingredients.begin(), ingredients.end(), items) != ingredients.end()) {

            v(tag, "Ingredients fed");

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

        if (!recipe->cook(ingredients)) {

            return false;
        }
    }
    return true;
}