#include <iostream>
#include <fstream>
#include <argparse/argparse.hpp>

#include "Utils.h"
#include "BuildConfig.h"
#include "VersionInfo.h"
#include "SQLParser.h"

using namespace Utils;
using namespace hsql;

auto read_file(std::string_view path) -> std::string {

    constexpr auto read_size = std::size_t(4096);
    auto stream = std::ifstream(path.data());
    stream.exceptions(std::ios_base::badbit);

    auto out = std::string();
    auto buf = std::string(read_size, '\0');
    while (stream.read(&buf[0], read_size)) {

        out.append(buf, 0, stream.gcount());
    }
    out.append(buf, 0, stream.gcount());
    return out;
}

void tokenize(std::string const &str, const char delim, std::list <std::string> &out) {

    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {

        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

int main(int argc, char *argv[]) {

    auto errTag = "error";
    auto parsingTag = "parsing";

    argparse::ArgumentParser program(VERSIONABLE_NAME, getVersion());

    program.add_argument("-i", "--input")
            .required()
            .help("The path for the input SQL file");

    program.add_argument("-o", "--output")
            .required()
            .help("The target programming language");

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

        auto input = program.get<std::string>("input");
        auto output = program.get<std::string>("output");

        i("processing", input);
        i("into --->", output);

        auto query = read_file(input);
        auto pos = query.find('\n');
        auto trace = std::list<std::string>();

        if (pos != std::string::npos) {

            tokenize(query, '\n', trace);
        }

        for (std::string row: trace) {

            v(parsingTag, row);
        }

        SQLParserResult result;
        SQLParser::parseSQLString(query, &result);

        if (result.isValid()) {

            auto count = result.size();

            v(parsingTag, "Completed");

            if (count > 0) {

                v(parsingTag, "Count: " + std::to_string(count));

                /**
                 * TODO: Access results
                 */

            } else {

                w(parsingTag, "No items");
            }

        } else {

            e(errTag, "Error while parsing file " + input);
            e(errTag, "Error at line: " + std::to_string(result.errorLine()));
            e(errTag, "Error at column: " + std::to_string(result.errorColumn()));
            std::exit(1);
        }


    } catch (std::logic_error &err) {

        e(errTag, err.what());
        std::exit(1);
    }
    return 0;
}