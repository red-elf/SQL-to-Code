//
// Created by milosvasic on 30.08.22.
//

#ifndef _CPPHEADERFILERECIPE_H
#define _CPPHEADERFILERECIPE_H

#include "string"
#include "../../IRecipe.h"

class CppHeaderFileRecipe : public IRecipe {

private:

public:

    CppHeaderFileRecipe() : IRecipe("C++ header file recipe") {}

    bool cook(std::vector<Ingredients *> &ingredients) override;
};


#endif //_CPPHEADERFILERECIPE_H
