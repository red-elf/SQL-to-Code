//
// Created by milosvasic on 28.08.22.
//

#ifndef _IPROCESSOR_H
#define _IPROCESSOR_H

template<class IN, class OUT>
class IProcessor {

public:

    virtual OUT process(IN &input) = 0;
};


#endif //_IPROCESSOR_H
