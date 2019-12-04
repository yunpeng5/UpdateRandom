#ifndef MstarFactory
#define MstarFactory

#include "dsFactory.h"
#include "star.h"

class starFactory:public dsFactory
{
public:
    star* create(int num,double *p);
};

#endif // MstarFactory
