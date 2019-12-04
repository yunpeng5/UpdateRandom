#ifndef MlazyAliasMethodFactory
#define MlazyAliasMethodFactory

#include "dsFactory.h"
#include "lazyAliasMethod.h"

class lazyAliasMethodFactory:public dsFactory
{
public:
    lazyAliasMethod* create(int num,double *p);
};

#endif // MlazyAliasMethodFactory
