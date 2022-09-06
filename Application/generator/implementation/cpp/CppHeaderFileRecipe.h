//
// Created by milosvasic on 30.08.22.
//

#ifndef _CPPHEADERFILERECIPE_H
#define _CPPHEADERFILERECIPE_H

#include "string"
#include "memory"
#include "../../IRecipe.h"
#include "CppRecipeCommons.h"

class CppHeaderFileRecipe : public IRecipe, public CppRecipeCommons {

private:

public:

    CppHeaderFileRecipe() : IRecipe("C++ header file recipe"), CppRecipeCommons() {}

    bool cook(std::vector<std::shared_ptr<Ingredients>> &ingredients) override;
};


#endif //_CPPHEADERFILERECIPE_H
