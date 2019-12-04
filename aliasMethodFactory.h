#ifndef MaliasMethodFactory
#define MaliasMethodFactory

#include "dsFactory.h"
#include "aliasMethod.h"

class aliasMethodFactory:public dsFactory
{
public:
    aliasMethod* create(int num,double *p);
};

#endif // MaliasMethodFactory
