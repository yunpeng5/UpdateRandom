#include "stdDiscreteFactory.h"
#include "stdDiscrete.h"

stdDiscrete* stdDiscreteFactory::create(int num,double *p)
{
    return new stdDiscrete(num,p);
}
