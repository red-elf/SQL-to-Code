//
// Created by milosvasic on 29.08.22.
//

#ifndef _INGREDIENTS_H
#define _INGREDIENTS_H

#include "vector"
#include "string"
#include "IIngredient.h"
#include "implementation/ClassNameIngredient.h"
#include "implementation/ClassPropertyIngredient.h"

class Ingredients {

private:

    std::string description;

    ClassNameIngredient *className;
    std::vector<ClassPropertyIngredient *> properties;

public:

    explicit Ingredients(std::string description);

    [[nodiscard]] std::string getDescription();

    void setClassName(ClassNameIngredient *className);

    [[nodiscard]] ClassNameIngredient *getClassName();

    [[nodiscard]] bool addProperty(ClassPropertyIngredient *property);

    [[nodiscard]] std::vector<ClassPropertyIngredient *> *getProperties();
};


#endif //_INGREDIENTS_H
