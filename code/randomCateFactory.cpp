#include "randomCateFactory.h"
#include "randomCate.h"

randomCate* randomCateFactory::create(int num,double *p)
{
    return new randomCate(num,p);
}
