//
// Created by milosvasic on 29.08.22.
//

#ifndef _IRECIPE_H
#define _IRECIPE_H

#include "vector"
#include "IIngredient.h"


class IRecipe {

public:

    virtual bool cook(std::vector<IIngredient *> &ingredients) = 0;
};


#endif //_IRECIPE_H
