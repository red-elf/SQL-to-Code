//
// Created by milosvasic on 30.08.22.
//

#include "CppHeaderFileRecipe.h"

#include "string"
#include "Utils.h"
#include "Commons.h"

using namespace Utils;
using namespace Commons::IO;

bool CppHeaderFileRecipe::cook(std::vector<std::shared_ptr<Ingredients>> &ingredients) {

    auto tag = getDescription();

    for (const std::shared_ptr<Ingredients>& ingredientsSet: ingredients) {

        auto classNameIngredient = ingredientsSet->getClassName();
        std::string className = getClassName(classNameIngredient);

        d(tag, "Class name: " + className);

        auto properties = ingredientsSet->getProperties();
        v(tag, "Class properties count: " + std::to_string(properties->size()));

        for (auto &&propertyIngredient: *properties) {

            std::string propertyName = getPropertyName(propertyIngredient);
            v(tag, "Class property: " + propertyName);
        }
    }

    return false;
}