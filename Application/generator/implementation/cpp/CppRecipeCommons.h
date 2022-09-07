//
// Created by milosvasic on 01.09.22.
//

#ifndef _CPPRECIPECOMMONS_H
#define _CPPRECIPECOMMONS_H

#include "string"
#include "memory"

#include "../ClassNameIngredient.h"

class CppRecipeCommons {

protected:

    static std::string getClassName(std::shared_ptr<ClassNameIngredient> &ingredient);
};


#endif //_CPPRECIPECOMMONS_H
