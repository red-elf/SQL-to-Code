//
// Created by milosvasic on 28.08.22.
//

#ifndef _RAWDATAPROCESSORRECIPE_H
#define _RAWDATAPROCESSORRECIPE_H

#include "string"
#include "IProcessor.h"

class RawDataProcessorRecipe : public IProcessor<std::string, const std::string> {

public:

    [[nodiscard]] const std::string process(std::string &input) override;
};


#endif //_RAWDATAPROCESSORRECIPE_H
