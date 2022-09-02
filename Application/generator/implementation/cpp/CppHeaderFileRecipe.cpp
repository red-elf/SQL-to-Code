//
// Created by milosvasic on 30.08.22.
//

#include "CppHeaderFileRecipe.h"

#include "string"
#include "Utils.h"
#include "../IngredientType.h"
#include "../../IIngredient.h"
#include "../../Ingredients.h"

using namespace Utils;

bool CppHeaderFileRecipe::cook(std::vector<Ingredients *> &ingredients) {

    auto tag = "recipe :: cook";

    for (Ingredients *ingredientsSet: ingredients) {

        for (IIngredient *ingredient: *ingredientsSet->getIngredients()) {

            std::string className;
            // FIXME:
            //IngredientType ingredientType = ingredient->getIngredientType();

//            switch(ingredientType) {
//
//                case IngredientType::CLASS_NAME: {
//
////                    ClassNameIngredient *classNameIngredient = dynamic_cast<ClassNameIngredient *>(ingredient);
////                    className = getClassName(classNameIngredient);
//                    v(tag, "Ingredient :: Class name");
//                    break;
//                }
//
//                case IngredientType::CLASS_PROPERTY: {
//
//                    v(tag, "Ingredient :: Class property");
//                    break;
//                }
//
//                default: {
//
//                    e(tag, "Ingredient :: Unknown");
//                }
//            }
        }
    }

    return false;
}