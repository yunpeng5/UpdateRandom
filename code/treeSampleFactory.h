#ifndef MtreeSampleFactory
#define MtreeSampleFactory

#include "dsFactory.h"
#include "treeSample.h"

class treeSampleFactory:public dsFactory
{
public:
    treeSample* create(int num,double *p);
};

#endif // MtreeSampleFactory
