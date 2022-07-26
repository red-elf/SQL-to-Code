//
// Created by milosvasic on 29.08.22.
//

#ifndef _CLASSPROPERTYINGREDIENT_H
#define _CLASSPROPERTYINGREDIENT_H

#include "string"
#include "../IIngredient.h"
#include "ClassPropertyDataType.h"

class ClassPropertyIngredient : public IIngredient {

public:

    ClassPropertyIngredient(std::string &name, ClassPropertyDataType &type) : IIngredient() {

        this->name = name;
        this->type = type;
    }

    std::string getName();

    ClassPropertyDataType &getType();

private:

    std::string name;

    ClassPropertyDataType type;
};


#endif //_CLASSPROPERTYINGREDIENT_H
