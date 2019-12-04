#include "aliasMethodFactory.h"
#include "aliasMethod.h"

aliasMethod* aliasMethodFactory::create(int num,double *p)
{
    return new aliasMethod(num,p);
}
