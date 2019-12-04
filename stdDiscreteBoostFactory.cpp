#include "stdDiscreteBoostFactory.h"
#include "stdDiscreteBoost.h"

stdDiscreteBoost* stdDiscreteBoostFactory::create(int num,double *p)
{
    return new stdDiscreteBoost(num,p);
}
