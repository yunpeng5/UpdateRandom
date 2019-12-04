#include "snaiveSampleFactory.h"
#include "snaiveSample.h"

snaiveSample* snaiveSampleFactory::create(int num,double *p)
{
    return new snaiveSample(num,p);
}
