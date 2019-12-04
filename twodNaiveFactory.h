#ifndef MtwodNaiveFactory
#define MtwodNaiveFactory

#include "dsFactory.h"
#include "twodNaive.h"

class twodNaiveFactory:public dsFactory
{
public:
    twodNaive* create(int num,double *p);
};

#endif // MtwodNaiveFactory
