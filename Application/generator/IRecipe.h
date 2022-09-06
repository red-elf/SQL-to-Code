//
// Created by milosvasic on 29.08.22.
//

#ifndef _IRECIPE_H
#define _IRECIPE_H

#include "vector"
#include "string"
#include "memory"
#include "Ingredients.h"

class IRecipe {

private:

    std::string description;

public:

    virtual ~IRecipe() = default;

    explicit IRecipe(std::string description);

    [[nodiscard]] std::string getDescription();

    [[nodiscard]] virtual bool cook(std::vector<std::shared_ptr<Ingredients>> &ingredients) = 0;
};


#endif //_IRECIPE_H
