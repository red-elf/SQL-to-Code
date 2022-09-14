//
// Created by milosvasic on 01.09.22.
//

#ifndef _CPPRECIPECOMMONS_H
#define _CPPRECIPECOMMONS_H

#include "string"
#include "memory"

#include "../ClassNameIngredient.h"
#include "../ClassPropertyIngredient.h"

class CppRecipeCommons {

public:

    explicit CppRecipeCommons(std::string &dest);

protected:

    std::string destination;

    static std::string getClassName(std::shared_ptr<ClassNameIngredient> &ingredient);

    static std::string getPropertyName(std::shared_ptr<ClassPropertyIngredient> &ingredient);

    static std::string getPropertyType(std::shared_ptr<ClassPropertyIngredient> &ingredient);

    static std::string getPropertyGetterSignature(std::shared_ptr<ClassPropertyIngredient> &ingredient);

    static std::string getPropertySetterSignature(std::shared_ptr<ClassPropertyIngredient> &ingredient);

    static std::string getPropertyGetterImplementation(

            std::shared_ptr<ClassNameIngredient> &classNameIngredient,
            std::shared_ptr<ClassPropertyIngredient> &propertyIngredient
    );

    static std::string getPropertySetterImplementation(

            std::shared_ptr<ClassNameIngredient> &classNameIngredient,
            std::shared_ptr<ClassPropertyIngredient> &propertyIngredient
    );
};


#endif //_CPPRECIPECOMMONS_H
