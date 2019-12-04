#ifndef MthreedSampleFactory
#define MthreedSampleFactory

#include "dsFactory.h"
#include "threedSample.h"

class threedSampleFactory:public dsFactory
{
public:
    threedSample* create(int num,double *p);
};

#endif // MthreedSampleFactory
