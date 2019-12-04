#include "treeSample.h"

#include <cmath>
using namespace std;

treeSample::treeSample(int num,double p[]) : gen(rd())
{
    n=num;
    tdstore=new double[2*n];
    for(int i=0;i<n;i++)tdstore[n+i]=p[i];
    for(int i=n-1;i>=1;i--)tdstore[i]=tdstore[i*2]+tdstore[i*2+1];
}

treeSample::~treeSample()
{
    delete [] tdstore;
}

const double* treeSample::table()
{
    return tdstore;
}

void treeSample::change(int index,double weight)
{
    int pos=n+index;
    tdstore[pos]=weight;
    while(pos>1)
    {
        int left=pos,right=pos;
        if(pos%2==0)right++;
        else left--;
        pos/=2;
        tdstore[pos]=tdstore[left]+tdstore[right];
    }
}

int treeSample::ransample()
{
    uniform_real_distribution<double> dr(0,tdstore[1]);
    double dart=dr(gen);
    int i=1;
    while(i<n){
        if(dart<tdstore[i*2]){
            i*=2;
        }
        else{
            dart-=tdstore[i*2];
            i=i*2+1;
        }
    }
    return i-n;
}
