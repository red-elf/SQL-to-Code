//
// Created by milosvasic on 28.08.22.
//

#ifndef _STRINGDATAPROCESSOR_H
#define _STRINGDATAPROCESSOR_H

#include "string"
#include "Commons.h"
#include "Utils.h"
#include "IProcessor.h"

class StringDataProcessor : public IProcessor<std::string, std::string> {

public:

    [[nodiscard]] std::string process(std::string &input) override;

private:

    const std::string parsingTag = "parsing";
    const std::string preparingTag = "preparing";

    static std::string trimRow(std::string &row);
    static std::string alignRow(std::string &row);
};


#endif //_STRINGDATAPROCESSOR_H
