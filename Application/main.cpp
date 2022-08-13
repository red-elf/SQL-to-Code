#include <argparse/argparse.hpp>

#include "Utils.h"

int main() {

    auto logger = Utils::createLogger();

    logger->log("ddl2code", "Hello!");

    return 0;
}