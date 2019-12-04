#include "randomNaiveFactory.h"
#include "randomNaive.h"

randomNaive* randomNaiveFactory::create(int num,double *p)
{
    return new randomNaive(num,p);
}
