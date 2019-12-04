#ifndef MsnaiveSampleFactory
#define MsnaiveSampleFactory

#include "dsFactory.h"
#include "snaiveSample.h"

class snaiveSampleFactory:public dsFactory
{
public:
    snaiveSample* create(int num,double *p);
};

#endif // MsnaiveSampleFactory
