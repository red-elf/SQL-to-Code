//
// Created by milosvasic on 28.08.22.
//

#include "StringDataProcessorRecipe.h"

using namespace Utils;
using namespace Commons::Strings;

std::string StringDataProcessorRecipe::trimRow(std::string &row) {

    row = trim(row);
    row = trim(row, " ");
    row = trim(row, ",");
    row = eraseBetween(row, "DROP", ";");
    row = eraseBetween(row, "CREATE INDEX", ";");
    row = eraseBetween(row, "CHECK", ")),");
    row = eraseBetween(row, "CHECK", "))");
    row = eraseBetween(row, "UNIQUE", "ABORT");

    return row;
}

std::string StringDataProcessorRecipe::alignRow(std::string &row) {

    auto appendTab = !hasBeginning(row, "(") &&
                     !hasBeginning(row, ")") &&
                     !hasBeginning(row, "CREATE");

    std::string toAppend;

    if (appendTab) {

        return "    " + row;
    }
    return row;
}

std::string StringDataProcessorRecipe::process(std::string &query) {

    v(preparingTag, "Removing comments: STARTED");
    query = removeComments(query);
    v(preparingTag, "Removing comments: COMPLETED");

    auto open = false;
    auto rows = std::vector<std::string>();

    tokenize(query, '\n', rows);

    v(preparingTag, "Cleaning up the unsupported statements: STARTED");

    std::vector<std::string> processedRows;

    for (std::string &row: rows) {

        if (debug) {

            v(preparingTag, "Before prepare: " + row);
        }

        row = trimRow(row);

        if (row.length() > 0) {

            row = alignRow(row);

            auto opening = "(";
            auto closing = ");";

            if (row == opening) {

                open = true;
            }

            if (row == closing) {

                open = false;

                auto previousIndex = processedRows.size() - 1;
                auto previousRow = processedRows.at(previousIndex);
                previousRow = removeAfter(previousRow, ",");
                processedRows.at(previousIndex) = previousRow;
            }

            if (open && row != opening && row != closing) {

                row.append(",");
            }

            processedRows.push_back(row.append("\n"));
        }

        if (debug) {

            v(preparingTag, "After prepare: " + row);
        }
    }

    v(preparingTag, "Cleaning up the unsupported statements: COMPLETED");

    if (logFull) {

        v(parsingTag, "The final sql:");
    }

    query = "";
    for (std::string &row: processedRows) {

        query.append(row);
        if (logFull) {

            v(parsingTag, trim(row, "\n"));
        }
    }

    return query;
}