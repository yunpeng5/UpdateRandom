#include "naiveSampleFactory.h"
#include "naiveSample.h"

naiveSample* naiveSampleFactory::create(int num,double *p)
{
    return new naiveSample(num,p);
}
