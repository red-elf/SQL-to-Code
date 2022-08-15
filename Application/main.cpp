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

void replaceAll(std::string &data, const std::string &toSearch, const std::string &replaceStr) {

    size_t pos = data.find(toSearch);

    while (pos != std::string::npos) {

        data.replace(pos, toSearch.size(), replaceStr);
        pos = data.find(toSearch, pos + replaceStr.size());
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


        // Set the memory buffer
        std::string query = read_file(input);
        replaceAll(query, "\t", " ");
        replaceAll(query, "\n", " ");
        replaceAll(query, "\r", " ");
        replaceAll(query, "  ", " ");

        v(parsingTag, query);

        SQLParserResult result;
        SQLParser::parseSQLString(query, &result);

        if (result.isValid()) {

            v(parsingTag, "Completed");

            /**
             * TODO: Access results
             */

        } else {

            e(errTag, "Error while parsing file " + input);
            std::exit(1);
        }


    } catch (std::logic_error &err) {

        e(errTag, err.what());
        std::exit(1);
    }
    return 0;
}