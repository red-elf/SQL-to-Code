//
// Created by milosvasic on 13.09.22.
//

#ifndef _CPPSOURCEFILERECIPE_H
#define _CPPSOURCEFILERECIPE_H

#include "string"
#include "memory"
#include "../../IRecipe.h"
#include "CppRecipeCommons.h"

class CppSourceFileRecipe : public IRecipe, public CppRecipeCommons {

private:

public:

    explicit CppSourceFileRecipe(std::string &destination) :
    IRecipe("C++ source file recipe"), CppRecipeCommons(destination) {}

    bool cook(std::vector<std::shared_ptr<Ingredients>> &ingredients) override;
};


#endif //_CPPSOURCEFILERECIPE_H
