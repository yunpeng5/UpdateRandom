#ifndef MrandomCateFactory
#define MrandomCateFactory

#include "dsFactory.h"
#include "randomCate.h"

class randomCateFactory:public dsFactory
{
public:
    randomCate* create(int num,double *p);
};

#endif // MrandomCateFactory
