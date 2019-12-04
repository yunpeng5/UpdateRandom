#include "naiveSample.h"
#include <algorithm>
using namespace std;

naiveSample::naiveSample(int num,double p[]) : gen(rd())
{
    dstore=new double[num];
    for(int i=0;i<num;i++)dstore[i]=p[i];
    n=num;
    prob=new double[n];
    init();
    flag=0;
}

void naiveSample::init()
{
    int i;
    sum=dstore[0];
    prob[0]=dstore[0];
    for(i=1;i<n;i++)prob[i]=prob[i-1]+dstore[i],sum+=dstore[i];
}

naiveSample::~naiveSample()
{
    delete [] prob;
    delete [] dstore;
}

int naiveSample::ransample()
{
    if(flag==1)
    {
        init();
        flag=0;
    }
    uniform_real_distribution<double> dr(0,sum);
    double dart=dr(gen);
    int de=0;
    de=(int)(lower_bound(prob,prob+n,dart)-prob);
    if(de==n)de=n-1;
    return de;
}

const double* naiveSample::table()
{
    return prob;
}

void naiveSample::change(int index,double weight)
{
    dstore[index]=weight;
    flag=1;
}
