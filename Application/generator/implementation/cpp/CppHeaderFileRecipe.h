//
// Created by milosvasic on 30.08.22.
//

#ifndef _CPPHEADERFILERECIPE_H
#define _CPPHEADERFILERECIPE_H

#include "../../IRecipe.h"


class CppHeaderFileRecipe : public IRecipe {

public:

    CppHeaderFileRecipe() : IRecipe("C++ header file recipe") {

    }

    bool cook(std::vector<Ingredients *> &ingredients) override;
};


#endif //_CPPHEADERFILERECIPE_H
