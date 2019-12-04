#ifndef MstdDiscreteFactory
#define MstdDiscreteFactory

#include "dsFactory.h"
#include "stdDiscrete.h"

class stdDiscreteFactory:public dsFactory
{
public:
    stdDiscrete* create(int num,double *p);
};

#endif // MstdDiscreteFactory
