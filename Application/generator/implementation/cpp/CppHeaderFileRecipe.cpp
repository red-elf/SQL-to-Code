//
// Created by milosvasic on 30.08.22.
//

#include "CppHeaderFileRecipe.h"

#include "string"
#include "Utils.h"
#include "../../IIngredient.h"
#include "../../Ingredients.h"
#include "../ClassNameIngredient.h"
#include "../ClassPropertyIngredient.h"

using namespace Utils;

bool CppHeaderFileRecipe::cook(std::vector<Ingredients *> &ingredients) {

    auto tag = "recipe :: cook";

    for (Ingredients *ingredientsSet: ingredients) {

        for (IIngredient *ingredient: *ingredientsSet->getIngredients()) {

            std::string className;
            auto classNameIngredient = static_cast<ClassNameIngredient *>(ingredient);
            // FIXME:
            auto *classPropertyIngredient = static_cast<ClassPropertyIngredient *>(ingredient);

            if (classNameIngredient != nullptr) {

                className = getClassName(classNameIngredient);
                v(tag, "Ingredient :: Class name: " + className);
                continue;
            }

            if (classPropertyIngredient != nullptr) {

                v(tag, "Ingredient :: Class property: " + classPropertyIngredient->getName());
                continue;
            }

            e(tag, "Ingredient :: Unknown");
        }
    }

    return false;
}