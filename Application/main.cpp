#include <argparse/argparse.hpp>

#include "Utils.h"
#include "BuildConfig.h"
#include "VersionInfo.h"

using namespace Utils;

int main(int argc, char *argv[]) {

    auto tag = "main";

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

        e(tag, err.what());
        std::exit(1);
    }

    try {

        auto input = program.get<std::string>("input");
        auto output = program.get<std::string>("output");

        i("processing", input);
        i("target", output);

        // TODO:

    } catch (std::logic_error &err) {

        e(tag, err.what());
        std::exit(1);
    }
    return 0;
}