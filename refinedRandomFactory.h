#ifndef MrefinedRandomFactory
#define MrefinedRandomFactory

#include "dsFactory.h"
#include "refinedRandom.h"

class refinedRandomFactory:public dsFactory
{
public:
    refinedRandom* create(int num,double *p);
};

#endif // MrefinedRandomFactory
