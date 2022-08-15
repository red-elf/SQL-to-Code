#include <iostream>
#include <argparse/argparse.hpp>
#include <openddlparser/OpenDDLParser.h>

#include "Utils.h"
#include "BuildConfig.h"
#include "VersionInfo.h"

using namespace Utils;
using namespace ODDLParser;

int main(int argc, char *argv[]) {

    auto errTag = "error";

    argparse::ArgumentParser program(VERSIONABLE_NAME, getVersion());

    program.add_argument("-i", "--input")
            .required()
            .help("The path for the input DDL file");

    program.add_argument("-o", "--output")
            .required()
            .help("The target programming language");

    std::string epilog("Project homepage: ");
    epilog.append(getHomepage());

    program.add_description(getDescription());
    program.add_epilog(epilog);

    try {

        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error &err) {

        e(errTag, err.what());
        std::exit(1);
    }

    try {

        auto input = program.get<std::string>("input");
        auto output = program.get<std::string>("output");

        i("processing", input);
        i("into --->", output);

        FILE *fileStream = fopen(input.c_str(), "r+");
        // obtain file size:
        fseek(fileStream, 0, SEEK_END);
        const size_t size = ftell(fileStream);
        rewind(fileStream);

        if (size > 0) {

            char *buffer = new char[size];
            const size_t readSize = fread(buffer, sizeof(char), size, fileStream);

            if (readSize != size) {

                e(errTag, "Obtained size is different to the file size");
                std::exit(1);
            }

            // Set the memory buffer
            OpenDDLParser theParser;
            theParser.setBuffer(buffer, size);

            if (theParser.parse()) {

                v("parsing", "Completed");

                // TODO: Access results

            } else {

                e(errTag, "Error while parsing file " + input);
                std::exit(1);
            }

        } else {

            e(errTag, "File size is zero");
            std::exit(1);
        }

    } catch (std::logic_error &err) {

        e(errTag, err.what());
        std::exit(1);
    }
    return 0;
}