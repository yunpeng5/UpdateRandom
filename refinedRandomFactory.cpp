#include "refinedRandomFactory.h"
#include "refinedRandom.h"

refinedRandom* refinedRandomFactory::create(int num,double *p)
{
    return new refinedRandom(num,p);
}
