//
// Created by milosvasic on 29.08.22.
//

#ifndef _CLASSNAMEINGREDIENT_H
#define _CLASSNAMEINGREDIENT_H

#include "string"
#include "../IIngredient.h"

class ClassNameIngredient : public IIngredient {

private:

    std::string name;

public:

    explicit ClassNameIngredient(std::string &name);

    std::string getName();
};


#endif //_CLASSNAMEINGREDIENT_H
