#include <iostream>
#include <vector>
#include <argparse/argparse.hpp>

#include "Utils.h"
#include "Commons.h"
#include "BuildConfig.h"
#include "VersionInfo.h"
#include "SQLParser.h"
#include "StringDataProcessor.h"
#include "sql/SQLStatement.h"
#include "processor/StringDataProcessorRecipe.h"
#include "generator/implementation/ClassNameIngredient.h"
#include "generator/implementation/ClassPropertyDataType.h"
#include "generator/implementation/ClassPropertyIngredient.h"

using namespace Utils;
using namespace hsql;
using namespace Commons::IO;

int main(int argc, char *argv[]) {

    auto errTag = "error";
    auto tableTag = "table";
    auto inputTag = "input";
    auto columnTag = "column";
    auto parsingTag = "parsing";
    auto workFileTag = "work file";
    auto processingTag = "processing";

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

        logFull = program["--logFull"] == true;
        debug = program["--debug"] == true && logFull;

        auto processed = 0;
        auto target = program.get<std::string>("target");
        auto output = program.get<std::string>("output");
        auto inputs = program.get<std::vector<std::string>>("input");

        for (std::string &input: inputs) {

            i(inputTag, input);
        }

        for (std::string &input: inputs) {

            i(processingTag, input);
            i("into --->", target);

            std::string query = readFile(input);

            if (query.length() == 0) {

                e(errTag, "Nothing loaded from the input file: " + input);
                std::exit(1);
            }

            StringDataProcessorRecipe recipe;
            StringDataProcessor processor;

            if (!processor.doRegister(&recipe)) {

                e(errTag, "Could not register the processing recipe");
                std::exit(1);
            }

            query = processor.process(query);

            const std::string workFile = (output + "/").append("work.")
                    .append(std::to_string(processed)).append(".sql");

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

                                ClassNameIngredient className(tableName);

                                d(tableTag, className.getName());

                                for (const auto column: *columns) {

                                    std::string columnName = column->name;
                                    auto columnType = column->type;
                                    auto dataType = columnType.data_type;

                                    try {

                                        auto commonType = dataTypeToString(dataType);
                                        auto classPropertyDataType = dataTypeToClassPropertyDataType(dataType);

                                        ClassPropertyIngredient classProperty(columnName, classPropertyDataType);

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
                            }
                        }
                    }

                } else {

                    w(parsingTag, "No items");
                }

            } else {

                e(errTag, "Error while parsing file " + workFile);

                if (logFull) {

                    e(errTag, result.errorMsg());
                    e(errTag, "Line: " + std::to_string(result.errorLine()));
                    e(errTag, "Column: " + std::to_string(result.errorColumn()));
                }

                std::exit(1);
            }
        }

    } catch (std::logic_error &err) {

        e(errTag, err.what());
        std::exit(1);
    }
    return 0;
}