#include "lazyAliasMethodFactory.h"
#include "lazyAliasMethod.h"

lazyAliasMethod* lazyAliasMethodFactory::create(int num,double *p)
{
    return new lazyAliasMethod(num,p);
}
