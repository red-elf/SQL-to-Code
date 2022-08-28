//
// Created by milosvasic on 28.08.22.
//

#include "RawDataProcessor.h"

const std::string RawDataProcessor::process(std::string &input) {

    for (IProcessor<std::string, const std::string> *processor: recipes) {

        input = processor->process(input);
    }
    return input;
}