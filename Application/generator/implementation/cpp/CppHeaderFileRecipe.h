//
// Created by milosvasic on 30.08.22.
//

#ifndef _CPPHEADERFILERECIPE_H
#define _CPPHEADERFILERECIPE_H

#include "../../IRecipe.h"


class CppHeaderFileRecipe : public IRecipe {

public:

    bool cook(std::vector<Ingredients *> &ingredients) override;
};


#endif //_CPPHEADERFILERECIPE_H
