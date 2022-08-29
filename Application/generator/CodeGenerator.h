//
// Created by milosvasic on 29.08.22.
//

#ifndef _CODEGENERATOR_H
#define _CODEGENERATOR_H

#include "vector"
#include "IRecipe.h"
#include "Ingredients.h"
#include "IRegistration.h"

class CodeGenerator : public IRegistration<IRecipe *> {

private:

    std::vector<IRecipe *> recipes;
    std::vector<Ingredients *> ingredients;

public:

    [[nodiscard]] bool feed(Ingredients *items);

    [[nodiscard]] bool doRegister(IRecipe *what) override;

    [[nodiscard]] bool doUnregister(IRecipe *&what) override;

    bool execute();
};


#endif //_CODEGENERATOR_H
