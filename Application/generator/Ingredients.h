//
// Created by milosvasic on 29.08.22.
//

#ifndef _INGREDIENTS_H
#define _INGREDIENTS_H

#include "vector"
#include "IIngredient.h"

class Ingredients {

private:

    std::vector<IIngredient *> ingredients;

public:

    [[nodiscard]] bool add(IIngredient *ingredient);
};


#endif //_INGREDIENTS_H
