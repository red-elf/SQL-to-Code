//
// Created by milosvasic on 29.08.22.
//

#ifndef _CLASSNAMEINGREDIENT_H
#define _CLASSNAMEINGREDIENT_H

#include "string"
#include "IngredientType.h"
#include "../IIngredient.h"

class ClassNameIngredient : public IIngredient {

public:

    explicit ClassNameIngredient(std::string &name) : IIngredient() {

        this->name = name;
    };

    std::string getName();

    IngredientType getIngredientType() override;

private:

    std::string name;
};


#endif //_CLASSNAMEINGREDIENT_H
