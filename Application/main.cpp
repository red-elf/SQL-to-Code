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

std::string trimRow(std::string &row) {

    row = trim(row);
    row = trim(row, " ");

    return row;
}

std::string stripRow(std::string &row) {

    row = eraseBetween(row, "DROP", ";");
    row = eraseBetween(row, "CREATE INDEX", ";");
    row = eraseBetween(row, "CHECK", ")),");
    row = eraseBetween(row, "CHECK", "))");
    row = eraseBetween(row, "UNIQUE", "ABORT");

    return row;
}

bool prepareRow(std::string &row) {

    row = trimRow(row);
    auto comma = hasEnding(row, ",");
    row = stripRow(row);

    return comma;
}

std::string alignRow(std::string &row) {

    auto appendTab = !hasBeginning(row, "(") &&
                     !hasBeginning(row, ")") &&
                     !hasBeginning(row, "CREATE");

    std::string toAppend;

    if (appendTab) {

        return "    " + row;
    }
    return row;
}

int main(int argc, char *argv[]) {

    auto errTag = "error";
    auto tableTag = "table";
    auto inputTag = "input";
    auto columnTag = "column";
    auto parsingTag = "parsing";
    auto workFileTag = "work file";
    auto preparingTag = "preparing";
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

        auto processed = 0;
        auto logFull = program["--logFull"] == true;
        auto debug = program["--debug"] == true && logFull;
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

            v(preparingTag, "Removing comments: STARTED");
            query = removeComments(query);
            v(preparingTag, "Removing comments: COMPLETED");

            auto rows = std::vector<std::string>();
            tokenize(query, '\n', rows);

            v(preparingTag, "Cleaning up the unsupported statements: STARTED");

            query = "";
            auto index = 0;

            for (std::string &row: rows) {

                if (debug) {

                    v(preparingTag, "Before prepare: " + row);
                }

                auto isEnclosed = prepareRow(row);

                if (row.length() > 0) {

                    row = alignRow(row);

                    auto isLastInEnclosed = false;

                    auto nextIndex = index;
                    while (nextIndex++ && nextIndex < rows.size()) {

                        auto nextRow = rows.at(nextIndex);
                        auto isNextRowEnclosed = prepareRow(nextRow);
                        isLastInEnclosed = hasBeginning(nextRow, ");");

                        if (isLastInEnclosed) {

                            break;
                        }
                    }

                    if (isEnclosed && !hasEnding(row, ",") && !isLastInEnclosed) {

                        row.append(",");
                    }

                    if (isLastInEnclosed) {

                        d(parsingTag, row);
                    }

                    if (isLastInEnclosed && hasEnding(row, " ,")) {

                        e(parsingTag, row);

                        row = removeAfter(row, ",");
                    }

                    query.append(row).append("\n");
                }

                if (debug) {

                    v(preparingTag, "After prepare: " + row);
                }

                index++;
            }

            v(preparingTag, "Cleaning up the unsupported statements: COMPLETED");

            if (logFull) {

                rows.clear();
                tokenize(query, '\n', rows);

                v(parsingTag, "The final sql:");

                for (std::string &row: rows) {

                    v(parsingTag, row);
                }
            }

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

                        auto type = statement->type();
                        if (type == StatementType::kStmtCreate) {

                            const auto *create = dynamic_cast<const hsql::CreateStatement *>(statement);
                            const auto tableName = create->tableName;
                            const auto columns = create->columns;

                            d(tableTag, tableName);
                            for (const auto column: *columns) {

                                auto columnName = column->name;
                                auto columnType = column->type;
                                auto dataType = columnType.data_type;

                                try {

                                    auto commonType = dataTypeToString(dataType);

                                    v(
                                            columnTag,

                                            std::string(tableName).append(" :: ")
                                                    .append(columnName).append(" -> ").append(commonType)
                                    );

                                } catch (std::invalid_argument &err) {

                                    e(errTag, err.what());
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