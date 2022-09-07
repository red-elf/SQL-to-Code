//
// Created by milosvasic on 30.08.22.
//

#include "CppHeaderFileRecipe.h"

#include "list"
#include "string"
#include "Utils.h"
#include "Commons.h"
#include "../../../Constants.h"

using namespace Utils;
using namespace Constants;
using namespace Commons::IO;
using namespace Commons::Strings;

bool CppHeaderFileRecipe::cook(std::vector<std::shared_ptr<Ingredients>> &ingredients) {

    auto tag = getDescription();
    auto newLine = lineBreak();

    for (const std::shared_ptr<Ingredients> &ingredientsSet: ingredients) {

        std::string content;

        auto classNameIngredient = ingredientsSet->getClassName();

        if (classNameIngredient->getName().length() == 0) {

            e(tag, "Empty class name");
            return false;
        }

        std::string className = getClassName(classNameIngredient);
        std::string fileName = className + ".h";
        std::string fileOutput = destination + fileSeparator() + fileName;

        d(tag, "Class name: " + className);
        d(tag, "Output: " + fileOutput);

        content.append(COMMENT_ON).append(newLine).append(newLine)
                .append(TAB).append(fileName).append(newLine)
                .append(TAB).append(SIGNATURE).append(newLine)
                .append(COMMENT_OFF).append(newLine);

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

        if (logFull()) {

            v(tag, "The header file content:");

            std::list<std::string> lines;
            tokenize(content, '\n', lines);

            for (const auto &line: lines) {

                v(tag, line);
            }
        }

        writeFile(content, fileOutput);
    }

    return false;
}