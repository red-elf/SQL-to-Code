//
// Created by milosvasic on 29.08.22.
//

#ifndef _CODEGENERATOR_H
#define _CODEGENERATOR_H

#include "vector"
#include "memory"
#include "IRecipe.h"
#include "Ingredients.h"
#include "IRegistration.h"
#include "IUnRegistration.h"

class CodeGenerator : public IRegistration<IRecipe>, IUnRegistration<IRecipe> {

private:

    std::vector<IRecipe *> recipes;
    std::vector<std::shared_ptr<Ingredients>> ingredients;

public:

    [[nodiscard]] bool feed(Ingredients &items);

    [[nodiscard]] bool doRegister(IRecipe &what) override;

    [[nodiscard]] bool doUnregister(IRecipe &what) override;

    bool execute();
};


#endif //_CODEGENERATOR_H
