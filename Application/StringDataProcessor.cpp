//
// Created by milosvasic on 28.08.22.
//

#include <algorithm>

#include "StringDataProcessor.h"

const std::string StringDataProcessor::process(std::string &input) {

    for (IProcessor<std::string, const std::string> *processor: recipes) {

        input = processor->process(input);
    }
    return input;
}

bool StringDataProcessor::doRegister(IProcessor<std::string, const std::string> *what) {

    if (std::find(recipes.begin(), recipes.end(), what) != recipes.end()) {

        return true;

    } else {

        recipes.push_back(what);

        if (std::find(recipes.begin(), recipes.end(), what) != recipes.end()) {

            return true;
        }
    }
    return false;
}

bool StringDataProcessor::doUnregister(IProcessor<std::string, const std::string> *&what) {

    if (std::find(recipes.begin(), recipes.end(), what) != recipes.end()) {

        recipes.erase(find(recipes.begin(), recipes.end(), what));

        if (std::find(recipes.begin(), recipes.end(), what) != recipes.end()) {

            return false;
        }
    }
    return true;
}