#ifndef MstdDiscreteBoostFactory
#define MstdDiscreteBoostFactory

#include "dsFactory.h"
#include "stdDiscreteBoost.h"

class stdDiscreteBoostFactory:public dsFactory
{
public:
    stdDiscreteBoost* create(int num,double *p);
};

#endif // MstdDiscreteBoostFactory
