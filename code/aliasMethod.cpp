#include "aliasMethod.h"

#include <queue>
using namespace std;

aliasMethod::aliasMethod(int num,double p[]) : gen(rd()), d(0,num-1), dr(0.0,1.0)
{
    dstore=new double[num];
    alias=new int[num];
    prob=new double[num];
    for(int i=0;i<num;i++)dstore[i]=p[i];
    n=num;
    init();
    flag=0;
}

void aliasMethod::init()
{
    //cout<<"alias"<<endl;
    queue<int> small;
    queue<int> large;
    double p[n];
    int i;
    double sum=0;
    for(i=0;i<n;i++)sum+=dstore[i];
    for(i=0;i<n;i++)
    {
        p[i]=dstore[i]*n/sum;
        if(p[i]<1)small.push(i);
        else large.push(i);
    }
    while((!small.empty())&&(!large.empty()))
    {
        int l=small.front();
        small.pop();
        int g=large.front();
        large.pop();
        prob[l]=p[l];
        alias[l]=g;
        p[g]=p[g]+p[l]-1;
        if(p[g]<1)small.push(g);
        else large.push(g);
    }
    while(!large.empty())
    {
        int g=large.front();
        large.pop();
        prob[g]=1;
        alias[g]=-1;
    }
    while(!small.empty())
    {
        int l=small.front();
        small.pop();
        prob[l]=1;
        alias[l]=-1;
    }
}

aliasMethod::~aliasMethod()
{
    delete [] alias;
    delete [] prob;
    delete [] dstore;
}

int aliasMethod::ransample()
{
    if(flag==1)
    {
        init();
        flag=0;
    }
    int sel=d(gen);
    double sel2=dr(gen);
    if(sel2<prob[sel]) return sel;
    else return alias[sel];
}

const int* aliasMethod::tableAlias()
{
    return alias;
}

const double* aliasMethod::tableProb()
{
    return prob;
}

void aliasMethod::change(int index,double weight)
{
    dstore[index]=weight;
    flag=1;
}
