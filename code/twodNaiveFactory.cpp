#include "twodNaiveFactory.h"
#include "twodNaive.h"

twodNaive* twodNaiveFactory::create(int num,double *p)
{
    return new twodNaive(num,p);
}

