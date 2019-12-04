#ifndef MrandomNaiveFactory
#define MrandomNaiveFactory

#include "dsFactory.h"
#include "randomNaive.h"

class randomNaiveFactory:public dsFactory
{
public:
    randomNaive* create(int num,double *p);
};

#endif // MrandomNaiveFactory
