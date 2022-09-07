//
// Created by milosvasic on 30.08.22.
//

#include "CppHeaderFileRecipe.h"

#include "string"
#include "Utils.h"
#include "Commons.h"

using namespace Utils;
using namespace Commons::IO;
using namespace Commons::Strings;

bool CppHeaderFileRecipe::cook(std::vector<std::shared_ptr<Ingredients>> &ingredients) {

    auto tag = getDescription();

    for (const std::shared_ptr<Ingredients>& ingredientsSet: ingredients) {

        auto classNameIngredient = ingredientsSet->getClassName();

        if (classNameIngredient->getName().length() == 0) {

            e(tag, "Empty class name");
            return false;
        }

        std::string className = getClassName(classNameIngredient);
        std::string fileOutput = destination + fileSeparator() + className + ".h";

        d(tag, "Class name: " + className);
        d(tag, "Output: " + fileOutput);

        auto properties = ingredientsSet->getProperties();
        v(tag, "Class properties count: " + std::to_string(properties->size()));

        for (auto &&propertyIngredient: *properties) {

            if (propertyIngredient->getName().length() == 0) {

                e(tag, "Empty property name");
                return false;
            }

            std::string propertyName = getPropertyName(propertyIngredient);
            v(tag, "Class property: " + propertyName);
        }
    }

    return false;
}