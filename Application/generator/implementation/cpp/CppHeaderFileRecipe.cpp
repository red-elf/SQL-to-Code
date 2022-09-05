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

        // FIXME:
//        for (std::unique_ptr<ClassPropertyIngredient> propertyIngredient: *ingredientsSet->getProperties()) {
//
//            v(tag, "Class property: " + propertyIngredient->getName());
//        }
    }

    return false;
}