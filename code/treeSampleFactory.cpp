#include "treeSampleFactory.h"
#include "treeSample.h"

treeSample* treeSampleFactory::create(int num,double *p)
{
    return new treeSample(num,p);
}
