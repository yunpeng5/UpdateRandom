#ifndef MheapSampleFactory
#define MheapSampleFactory

#include "dsFactory.h"
#include "heapSample.h"

class heapSampleFactory:public dsFactory
{
public:
    heapSample* create(int num,double *p);
};

#endif // MheapSampleFactory
