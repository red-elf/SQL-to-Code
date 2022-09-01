//
// Created by milosvasic on 30.08.22.
//

#include "CppHeaderFileRecipe.h"

#include "string"
#include "Utils.h"
#include "../../IIngredient.h"
#include "../../Ingredients.h"

using namespace Utils;

bool CppHeaderFileRecipe::cook(std::vector<Ingredients *> &ingredients) {

    auto tag = "recipe :: cook";

    for (Ingredients *ingredientsSet: ingredients) {

        for (IIngredient *ingredient: *ingredientsSet->getIngredients()) {

            std::string className = "";

            // FIXME:
            ClassNameIngredient *classNameIngredient = dynamic_cast<ClassNameIngredient *>(ingredient);
            if (classNameIngredient != nullptr) {

                className = getClassName(classNameIngredient);
                v(tag, "Ingredient :: Class name");

            } else {

                w(tag, "Ingredient :: Unknown");
            }
        }
    }

    return false;
}