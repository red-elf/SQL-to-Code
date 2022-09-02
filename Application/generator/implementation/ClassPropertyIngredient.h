//
// Created by milosvasic on 29.08.22.
//

#ifndef _CLASSPROPERTYINGREDIENT_H
#define _CLASSPROPERTYINGREDIENT_H

#include "string"
#include "../IIngredient.h"
#include "IngredientType.h"
#include "ClassPropertyDataType.h"

class ClassPropertyIngredient : public IIngredient {

public:

    ClassPropertyIngredient(std::string &name, ClassPropertyDataType &type);

    std::string getName();

    ClassPropertyDataType &getType();

    IngredientType getIngredientType() override;

private:

    std::string name;

    ClassPropertyDataType &type;
};


#endif //_CLASSPROPERTYINGREDIENT_H
