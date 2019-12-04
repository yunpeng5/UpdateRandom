#include "randomNaive.h"

randomNaive::randomNaive(int num,double p[]) : gen(rd()), d(0,num-1), dr(0.0,1.0)
{
    n=num;
    prob=new double[n];
    int i;
    maxn=-1;
    for(i=0;i<n;i++){prob[i]=p[i];if(p[i]>maxn)maxn=p[i];}
}

randomNaive::~randomNaive()
{
    delete [] prob;
}

int randomNaive::ransample()
{
    int dart;
    while(1)
    {
        dart=d(gen);
        double pr=dr(gen);
        if(pr<prob[dart]/maxn)break;
    }
    return dart;
}

const double* randomNaive::table()
{
    return prob;
}

void randomNaive::change(int index,double weight)
{
    if(weight>maxn)maxn=weight;
    prob[index]=weight;
}
