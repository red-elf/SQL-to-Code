//
// Created by milosvasic on 29.08.22.
//

#ifndef _IINGREDIENT_H
#define _IINGREDIENT_H

#include "implementation/IngredientType.h"

class IIngredient {

public:

    IIngredient();

    virtual ~IIngredient() = default;

    virtual IngredientType getIngredientType() = 0;
};


#endif //_IINGREDIENT_H
