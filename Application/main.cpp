#include <iostream>
#include <vector>
#include <argparse/argparse.hpp>

#include "Utils.h"
#include "Target.h"
#include "Commons.h"
#include "BuildConfig.h"
#include "VersionInfo.h"
#include "SQLParser.h"
#include "sql/SQLStatement.h"
#include "processor/StringDataProcessor.h"
#include "generator/Ingredients.h"
#include "generator/CodeGenerator.h"
#include "generator/implementation/ClassNameIngredient.h"
#include "generator/implementation/ClassPropertyIngredient.h"
#include "generator/implementation/cpp/CppHeaderFileRecipe.h"
#include "generator/implementation/cpp/CppSourceFileRecipe.h"

using namespace Utils;
using namespace hsql;
using namespace Target;
using namespace Commons::IO;
using namespace Commons::Strings;

int main(int argc, char *argv[]) {

    auto errTag = "error";
    auto tableTag = "table";
    auto inputTag = "input";
    auto columnTag = "column";
    auto parsingTag = "parsing";
    auto paramsTag = "parameters";
    auto workFileTag = "work file";
    auto processingTag = "processing";
    auto codeGeneratorTag = "code generator";

    CodeGenerator codeGenerator;
    StringDataProcessor processor;

    argparse::ArgumentParser program(VERSIONABLE_NAME, getVersion());

    program.add_argument("-i", "--input")
            .required()
            .nargs(1, 1000)
            .help("The path for the input SQL file");

    program.add_argument("-t", "--target")
            .required()
            .help("The target programming language");

    program.add_argument("-o", "--output")
            .required()
            .help("The destination output directory");

    program.add_argument("-l", "--logFull")
            .default_value(false)
            .implicit_value(true)
            .help("Log with the full details");

    program.add_argument("-d", "--debug")
            .default_value(false)
            .implicit_value(true)
            .help("Additional information related to the parsing and code generating");

    std::string epilog("Project homepage: ");
    epilog.append(getHomepage());

    program.add_description(getDescription());
    program.add_epilog(epilog);

    try {

        program.parse_args(argc, argv);

    } catch (const std::runtime_error &err) {

        e(errTag, err.what());
        std::exit(1);
    }

    try {

        setLogFull(program["--logFull"] == true);
        setDebug(program["--debug"] == true && logFull());

        if (logFull()) {

            v(paramsTag, "Full-log mode is on");
        }

        if (isDebug()) {

            w(paramsTag, "Debug mode is on");
        }

        auto processed = 0;
        auto targetInput = program.get<std::string>("target");
        auto output = program.get<std::string>("output");
        auto inputs = program.get<std::vector<std::string>>("input");

        auto target = ETarget::UNKNOWN;

        if (targetInput == Target::CPP) {

            target = ETarget::CPP;
        }

        if (targetInput == Target::JVM) {

            target = ETarget::JVM;
        }

        if (targetInput == Target::DART) {

            target = ETarget::DART;
        }

        if (target == Target::ETarget::UNKNOWN) {

            e(errTag, "Unrecognized target: " + targetInput);
            std::exit(1);
        }

        // TODO: Instantiate only needed recipes
        CppHeaderFileRecipe cppHeaderFileRecipe(output);
        CppSourceFileRecipe cppSourceFileRecipe(output);

        for (std::string &input: inputs) {

            i(inputTag, input);
        }

        for (std::string &input: inputs) {

            i(processingTag, input);
            i("into --->", targetInput);

            std::string query = readFile(input);

            if (query.length() == 0) {

                e(errTag, "Nothing loaded from the input file: " + input);
                std::exit(1);
            }

            query = processor.process(query);

            const std::string workFile = (output + fileSeparator())
                    .append("work.")
                    .append(std::to_string(processed))
                    .append(".sql");

            d(workFileTag, workFile);

            writeFile(query, workFile);
            processed++;

            d(workFileTag, (workFile + " << ").append(input));

            SQLParserResult result;
            SQLParser::parseSQLString(query, &result);

            if (result.isValid()) {

                auto count = result.size();

                v(parsingTag, "Completed");

                if (count > 0) {

                    v(parsingTag, "Statements count: " + std::to_string(count));

                    auto statements = result.getStatements();
                    for (const auto statement: statements) {

                        if (statement->isType(hsql::kStmtCreate)) {

                            const auto *create = dynamic_cast<const hsql::CreateStatement *>(statement);
                            const auto createType = create->type;

                            if (createType == CreateType::kCreateTable) {

                                std::string tableName = create->tableName;
                                auto columns = create->columns;

                                Ingredients ingredients(tableName);
                                ClassNameIngredient className(tableName);

                                d(tableTag, className.getName());

                                ingredients.setClassName(className);

                                for (auto column: *columns) {

                                    std::string columnName = column->name;
                                    auto columnType = column->type;
                                    auto dataType = columnType.data_type;

                                    try {

                                        auto commonType = dataTypeToString(dataType);
                                        auto classPropertyDataType = dataTypeToClassPropertyDataType(dataType);

                                        ClassPropertyIngredient classProperty(columnName, classPropertyDataType);

                                        if (!ingredients.addProperty(classProperty)) {

                                            e(errTag, "Could not add the class property ingredient");
                                            std::exit(1);
                                        }

                                        v(
                                                columnTag,

                                                std::string(tableName).append(" :: ")
                                                        .append(classProperty.getName())
                                                        .append(" -> ")
                                                        .append(commonType)
                                        );

                                    } catch (std::invalid_argument &err) {

                                        e(errTag, err.what());
                                        std::exit(1);
                                    }
                                }

                                if (codeGenerator.feed(ingredients)) {

                                    if (isDebug()) {

                                        v(

                                                tableTag, "The ingredient fed: '"
                                                          + ingredients.getDescription() + "'"
                                        );
                                    }

                                } else {

                                    e(

                                            errTag, "The ingredient not fed: '"
                                                    + ingredients.getDescription() + "'"
                                    );

                                    std::exit(1);
                                }
                            }
                        }
                    }

                } else {

                    w(parsingTag, "No items");
                }

            } else {

                e(errTag, "Error while parsing file " + workFile);

                if (logFull()) {

                    e(errTag, result.errorMsg());
                    e(errTag, "Line: " + std::to_string(result.errorLine()));
                    e(errTag, "Column: " + std::to_string(result.errorColumn()));
                }

                std::exit(1);
            }
        }

        if (logFull()) {

            std::string recipesTarget = targetInput;
            if (target == Target::ETarget::CPP) {

                recipesTarget = "C++";
            }

            v(codeGeneratorTag, "Setting up the recipes for " + recipesTarget);
        }

        if (target == Target::ETarget::CPP) {

            if (codeGenerator.doRegister(cppHeaderFileRecipe)) {

                if (logFull()) {

                    v(

                            codeGeneratorTag,
                            "The " + cppHeaderFileRecipe.getDescription() + " has been registered"
                    );
                }

            } else {

                e(errTag, "Could not register the " + cppHeaderFileRecipe.getDescription());
                std::exit(1);
            }

            if (codeGenerator.doRegister(cppSourceFileRecipe)) {

                if (logFull()) {

                    v(

                            codeGeneratorTag,
                            "The " + cppSourceFileRecipe.getDescription() + " has been registered"
                    );
                }

            } else {

                e(errTag, "Could not register the " + cppSourceFileRecipe.getDescription());
                std::exit(1);
            }
        }

        if (codeGenerator.execute()) {

            v(codeGeneratorTag, "Success");

        } else {

            e(codeGeneratorTag, "Failure");
            std::exit(1);
        }

    } catch (std::logic_error &err) {

        e(errTag, err.what());
        std::exit(1);
    }
    return 0;
}