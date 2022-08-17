#include <iostream>
#include <argparse/argparse.hpp>

#include "Utils.h"
#include "BuildConfig.h"
#include "VersionInfo.h"
#include "SQLParser.h"
#include "sql/SQLStatement.h"
#include "Commons.h"

using namespace Utils;
using namespace hsql;
using namespace Commons::IO;
using namespace Commons::Strings;

int main(int argc, char *argv[]) {

    auto errTag = "error";
    auto tableTag = "table";
    auto parsingTag = "parsing";

    argparse::ArgumentParser program(VERSIONABLE_NAME, getVersion());

    program.add_argument("-i", "--input")
            .required()
            .help("The path for the input SQL file");

    program.add_argument("-o", "--output")
            .required()
            .help("The target programming language");

    program.add_argument("-l", "--logFull")
            .default_value(false)
            .implicit_value(true)
            .help("Log with the full details");

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

        auto logFull = program["--logFull"] == true;
        auto input = program.get<std::string>("input");
        auto output = program.get<std::string>("output");

        i("processing", input);
        i("into --->", output);

        auto query = read_file(input);

        if (logFull) {

            auto trace = std::list<std::string>();

            tokenize(query, '\n', trace);

            for (std::string &row: trace) {

                v(parsingTag, row);
            }
        }

        SQLParserResult result;
        SQLParser::parseSQLString(query, &result);

        if (result.isValid()) {

            auto count = result.size();

            v(parsingTag, "Completed");

            if (count > 0) {

                v(parsingTag, "Statements count: " + std::to_string(count));

                auto statements = result.getStatements();
                for (const SQLStatement *statement: statements) {

                    auto type = statement->type();
                    if (type == StatementType::kStmtCreate) {

                        const auto *create = dynamic_cast<const hsql::CreateStatement *>(statement);
                        v(tableTag, create->tableName);
                    }
                }

            } else {

                w(parsingTag, "No items");
            }

        } else {

            e(errTag, "Error while parsing file " + input);

            if (logFull) {

                e(errTag, result.errorMsg());
                e(errTag, "Line: " + std::to_string(result.errorLine()));
                e(errTag, "Column: " + std::to_string(result.errorColumn()));
            }

            std::exit(1);
        }

    } catch (std::logic_error &err) {

        e(errTag, err.what());
        std::exit(1);
    }
    return 0;
}