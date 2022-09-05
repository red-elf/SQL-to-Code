//
// Created by milosvasic on 29.08.22.
//

#ifndef _INGREDIENTS_H
#define _INGREDIENTS_H

#include "vector"
#include "string"
#include "memory"
#include "IIngredient.h"
#include "implementation/ClassNameIngredient.h"
#include "implementation/ClassPropertyIngredient.h"

class Ingredients {

private:

    std::string description;

    ClassNameIngredient *className{};
    std::vector<std::unique_ptr<ClassPropertyIngredient>> properties;

public:

    explicit Ingredients(std::string description);

    [[nodiscard]] std::string getDescription();

    void setClassName(ClassNameIngredient *name);

    [[nodiscard]] ClassNameIngredient *getClassName();

    [[nodiscard]] bool addProperty(std::unique_ptr<ClassPropertyIngredient>& property);

    [[nodiscard]] std::vector<std::unique_ptr<ClassPropertyIngredient>> *getProperties();
};


#endif //_INGREDIENTS_H
