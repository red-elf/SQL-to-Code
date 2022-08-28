//
// Created by milosvasic on 28.08.22.
//

#ifndef _RAWDATAPROCESSOR_H
#define _RAWDATAPROCESSOR_H

#include "string"
#include "vector"
#include "IProcessor.h"

class RawDataProcessor : public IProcessor<std::string, const std::string> {

public:

    [[nodiscard]] const std::string process(std::string &input) override;

private:

    const std::vector<IProcessor<std::string, const std::string>*> recipes;
};


#endif //_RAWDATAPROCESSOR_H
