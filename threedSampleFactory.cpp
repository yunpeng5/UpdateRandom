#include "threedSampleFactory.h"
#include "threedSample.h"

threedSample* threedSampleFactory::create(int num,double *p)
{
    return new threedSample(num,p);
}

