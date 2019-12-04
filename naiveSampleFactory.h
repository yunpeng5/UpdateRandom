#ifndef MnaiveSampleFactory
#define MnaiveSampleFactory

#include "dsFactory.h"
#include "naiveSample.h"

class naiveSampleFactory:public dsFactory
{
public:
    naiveSample* create(int num,double *p);
};

#endif // MnaiveSampleFactory
