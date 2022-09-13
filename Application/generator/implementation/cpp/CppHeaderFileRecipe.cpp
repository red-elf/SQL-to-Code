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
        // TODO: Separate files in the destination directory by the type:
        std::string fileOutput = destination + fileSeparator() + fileName;

        d(tag, "Class name: " + className);
        d(tag, "Output file: " + fileOutput);

        bool hasString = false;
        auto properties = ingredientsSet->getProperties();
        for (auto &&propertyIngredient: *properties) {

            if (propertyIngredient->getType() == ClassPropertyDataType::STRING) {

                hasString = true;
            }
        }

        content.append(COMMENT_ON).append(newLine)
                .append(TAB).append(fileName).append(newLine)
                .append(TAB).append(SIGNATURE).append(newLine)
                .append(COMMENT_OFF).append(newLine)
                .append(newLine);

        if (hasString) {

            content.append("#include \"string\"").append(newLine).append(newLine);
        }

        content.append(CLASS).append(" ").append(className).append(" ").append(BLOCK_ON)
                .append(newLine).append(newLine);

        if (logFull()) {

            v(tag, "Class properties count: " + std::to_string(properties->size()));
        }

        content.append("private:").append(newLine);

        for (auto &&propertyIngredient: *properties) {

            if (propertyIngredient->getName().length() == 0) {

                e(tag, "Empty property name");
                return false;
            }

            auto propertyName = getPropertyName(propertyIngredient);
            auto dataType = getPropertyType(propertyIngredient);

            if (dataType.empty()) {

                e(tag, "Empty property type");
                return false;
            }

            if (logFull()) {

                auto msg = std::string("Class property: ")
                        .append(propertyName)
                        .append(" (")
                        .append(dataType)
                        .append(")");

                v(tag, msg);
            }

            content.append(TAB).append(dataType).append(" ").append(propertyName).append(STATEMENT_END).append(newLine);
        }

        content.append(newLine).append("public:").append(newLine);

        for (auto &&propertyIngredient: *properties) {

            auto propertyGetter = getPropertyGetterSignature(propertyIngredient);
            auto propertySetter = getPropertySetterSignature(propertyIngredient);

            content.append(TAB).append(propertyGetter).append(newLine)
                    .append(TAB).append(propertySetter).append(newLine);
        }

        content.append(BLOCK_OFF).append(STATEMENT_END);

        if (logFull()) {

            v(tag, "The C++ header file content:");

            std::list<std::string> lines;
            tokenize(content, '\n', lines);

            for (const auto &line: lines) {

                v(tag, line);
            }
        }

        d(tag, "Writing the C++ header file: " + fileOutput);

        if (writeFileWithResult(content, fileOutput)) {

            i(tag, "The C++ header file written: " + fileOutput);

        } else {

            return false;
        }
    }

    return true;
}