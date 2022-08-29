//
// Created by milosvasic on 29.08.22.
//

#ifndef _IGENERATOR_H
#define _IGENERATOR_H

#include "vector"
#include "IIngredient.h"

class IGenerator {

private:

    std::vector<IIngredient *> ingredients;

public:

    [[nodiscard]] bool feed(IIngredient *ingredient);

    virtual bool execute() = 0;
};


#endif //_IGENERATOR_H
