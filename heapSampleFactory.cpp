#include "heapSampleFactory.h"
#include "heapSample.h"

heapSample* heapSampleFactory::create(int num,double *p)
{
    return new heapSample(num,p);
}
