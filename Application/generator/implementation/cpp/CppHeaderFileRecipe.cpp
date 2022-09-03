//
// Created by milosvasic on 30.08.22.
//

#include "CppHeaderFileRecipe.h"

#include "string"
#include "Utils.h"

using namespace Utils;

bool CppHeaderFileRecipe::cook(std::vector<Ingredients *> &ingredients) {

    auto tag = getDescription();

    for (Ingredients *ingredientsSet: ingredients) {

        auto classNameIngredient = ingredientsSet->getClassName();
        std::string className = getClassName(classNameIngredient);

        v(tag, "Class name: " + className);

        for (ClassPropertyIngredient *propertyIngredient: *ingredientsSet->getProperties()) {

            // FIXME: Segmentation fault
            w(tag, "Class property: FIXME");
            // v(tag, "Class property: " + propertyIngredient->getName());
        }
    }

    return false;
}