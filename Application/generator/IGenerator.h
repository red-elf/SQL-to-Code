//
// Created by milosvasic on 29.08.22.
//

#ifndef _IGENERATOR_H
#define _IGENERATOR_H

#include "vector"
#include "IRecipe.h"
#include "IIngredient.h"
#include "IRegistration.h"

class IGenerator : public IRegistration<IRecipe *> {

private:

    std::vector<IRecipe *> recipes;
    std::vector<IIngredient *> ingredients;

public:

    [[nodiscard]] bool feed(IIngredient *ingredient);

    [[nodiscard]] bool doRegister(IRecipe *what) override;

    [[nodiscard]] bool doUnregister(IRecipe *&what) override;

    bool execute();
};


#endif //_IGENERATOR_H
