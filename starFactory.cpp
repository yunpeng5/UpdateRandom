#include "starFactory.h"
#include "star.h"

star* starFactory::create(int num,double *p)
{
    return new star(num,p);
}

