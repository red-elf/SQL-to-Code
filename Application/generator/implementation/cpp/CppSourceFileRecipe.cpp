//
// Created by milosvasic on 13.09.22.
//

#include "CppSourceFileRecipe.h"

#include "list"
#include "string"
#include "Utils.h"
#include "Commons.h"
#include "../../../Constants.h"

using namespace Utils;
using namespace Constants;
using namespace Commons::IO;
using namespace Commons::Strings;

bool CppSourceFileRecipe::cook(std::vector<std::shared_ptr<Ingredients>> &ingredients) {

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
        std::string fileName = className + ".cpp";
        std::string headerFileName = className + ".h";

        // TODO: Separate files in the destination directory by the type:
        std::string fileOutput = destination + fileSeparator() + fileName;

        d(tag, "Class name: " + className);
        d(tag, "Output file: " + fileOutput);

        content.append(COMMENT_ON).append(newLine)
                .append(TAB).append(fileName).append(newLine)
                .append(TAB).append(SIGNATURE).append(newLine)
                .append(COMMENT_OFF).append(newLine)
                .append(newLine)
                .append("#include \"" + headerFileName + "\"").append(newLine).append(newLine);

        auto properties = ingredientsSet->getProperties();

        for (auto &&propertyIngredient: *properties) {

            auto propertyGetter = getPropertyGetterImplementation(classNameIngredient, propertyIngredient);
            auto propertySetter = getPropertySetterImplementation(classNameIngredient, propertyIngredient);

            content.append(propertyGetter).append(newLine).append(newLine)
                    .append(propertySetter).append(newLine).append(newLine);
        }

        if (logFull()) {

            v(tag, "The C++ source file content:");

            std::list<std::string> lines;
            tokenize(content, '\n', lines);

            for (const auto &line: lines) {

                v(tag, line);
            }
        }

        d(tag, "Writing the C++ source file: " + fileOutput);

        if (writeFileWithResult(content, fileOutput)) {

            i(tag, "The C++ source file written: " + fileOutput);

        } else {

            return false;
        }
    }

    return true;
}
