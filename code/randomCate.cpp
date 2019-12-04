#include "randomCate.h"

randomCate::randomCate(int num,double p[]) : gen(rd()), dr(0.0,1.0)
{
    n=num;
    prob=new double[n];
    posi=new int[n];
    nzn=0;
    rposi=new int[n];
    int i;
    maxn=-1;
    for(i=0;i<n;i++)
    {
        prob[i]=p[i];
        if(p[i]>maxn)maxn=p[i];
        if(p[i]!=0){posi[nzn]=i;rposi[i]=nzn;nzn++;}
    }
}

randomCate::~randomCate()
{
    delete [] prob;
    delete [] posi;
    delete [] rposi;
}

int randomCate::ransample()
{
    if(nzn==0)perror("number of positive weight cannot be equal to 0");
    int dart;
    while(1)
    {
        uniform_int_distribution<int> d(0,nzn-1);
        dart=d(gen);
        double pr=dr(gen);
        if(pr<prob[posi[dart]]/maxn)break;
    }
    return posi[dart];
}

const double* randomCate::table()
{
    return prob;
}

void randomCate::change(int index,double weight)
{
    if(weight>maxn)maxn=weight;
    if(prob[index]==0)
    {
        posi[nzn]=index;
        rposi[index]=nzn;
        nzn++;
    }
    if(weight==0)
    {
        posi[rposi[index]]=posi[nzn-1];
        nzn--;
    }
    prob[index]=weight;
}
