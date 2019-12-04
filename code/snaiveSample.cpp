#include "snaiveSample.h"

snaiveSample::snaiveSample(int num,double p[]) : gen(rd())
{
    n=num;
    prob=new double[n];
    int i;
    sum=0;
    for(i=0;i<n;i++)prob[i]=p[i],sum+=p[i];
}

snaiveSample::~snaiveSample()
{
    delete [] prob;
}

int snaiveSample::ransample()
{
    uniform_real_distribution<double> dr(0,sum);
    double dart=dr(gen);
    int de=0;
    while(dart>=prob[de]&&de<n)dart-=prob[de],de++;
    return de;
}

const double* snaiveSample::table()
{
    return prob;
}

void snaiveSample::change(int index,double weight)
{
    sum=sum-prob[index]+weight;
    prob[index]=weight;
}
