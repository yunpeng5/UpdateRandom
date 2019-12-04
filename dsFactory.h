#ifndef MdsFactory
#define MdsFactory

#include "baseDiscrete.h"

class dsFactory
{
public:
    virtual baseDiscrete* create(int num,double *p)=0;
};

#endif // MdsFactory
