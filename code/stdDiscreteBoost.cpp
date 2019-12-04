#include "stdDiscreteBoost.h"

stdDiscreteBoost::stdDiscreteBoost(int num,double *w) : gen(rd())
{
    //std::cout<<"std"<<endl;
    n=num;
    dstore=new double[num];
    for(int i=0;i<num;i++)dstore[i]=w[i];
    d=boost::random::discrete_distribution<int>(w,w+num);
    flag=0;
}

stdDiscreteBoost::~stdDiscreteBoost()
{
    delete [] dstore;
}

int stdDiscreteBoost::ransample()
{
    if(flag==1)
    {
        d=boost::random::discrete_distribution<int>(dstore,dstore+n);
        flag=0;
    }
    return (d)(gen);
}

void stdDiscreteBoost::change(int index,double weight)
{
    //delete d;
    dstore[index]=weight;
    flag=1;
    //d=new discrete_distribution<>(dstore,dstore+n);
}
