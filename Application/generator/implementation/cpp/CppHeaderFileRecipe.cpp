//
// Created by milosvasic on 30.08.22.
//

#include "CppHeaderFileRecipe.h"

#include "Utils.h"
#include "../../IIngredient.h"
#include "../../Ingredients.h"

using namespace Utils;

bool CppHeaderFileRecipe::cook(std::vector<Ingredients *> &ingredients) {

    auto tag = "recipe :: cook";

    for (Ingredients* ingredientsSet : ingredients) {

        for (IIngredient* ingredient : *ingredientsSet->getIngredients()) {

            v(tag, "Ingredient ...");
        }
    }

    return false;
}