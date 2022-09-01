//
// Created by milosvasic on 29.08.22.
//

#ifndef _INGREDIENTS_H
#define _INGREDIENTS_H

#include "vector"
#include "string"
#include "IIngredient.h"

class Ingredients {

private:

    std::string description;

    std::vector<IIngredient *> ingredients;

public:

    explicit Ingredients(std::string description);

    [[nodiscard]] bool add(IIngredient *ingredient);

    [[nodiscard]] std::string getDescription();

    [[nodiscard]] std::vector<IIngredient *> *getIngredients();
};


#endif //_INGREDIENTS_H
