//
// Created by milosvasic on 29.08.22.
//

#ifndef _CODEGENERATOR_H
#define _CODEGENERATOR_H

#include "vector"
#include "IRecipe.h"
#include "IIngredient.h"
#include "IRegistration.h"

class CodeGenerator : public IRegistration<IRecipe *> {

private:

    std::vector<IRecipe *> recipes;
    std::vector<IIngredient *> ingredients;

public:

    [[nodiscard]] bool feed(IIngredient *ingredient);

    [[nodiscard]] bool doRegister(IRecipe *what) override;

    [[nodiscard]] bool doUnregister(IRecipe *&what) override;

    bool execute();
};


#endif //_CODEGENERATOR_H
