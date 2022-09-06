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
    std::shared_ptr<ClassNameIngredient> className;
    std::vector<std::shared_ptr<ClassPropertyIngredient>> properties;

public:

    explicit Ingredients(std::string description);

    [[nodiscard]] std::string &getDescription();

    void setClassName(ClassNameIngredient &name);

    [[nodiscard]] std::shared_ptr<ClassNameIngredient> getClassName();

    [[nodiscard]] bool addProperty(ClassPropertyIngredient &property);

    [[nodiscard]] std::vector<std::shared_ptr<ClassPropertyIngredient>> *getProperties();
};


#endif //_INGREDIENTS_H
