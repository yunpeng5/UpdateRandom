#include "threedSample.h"

#include <cmath>
using namespace std;

threedSample::threedSample(int num,double p[]) : gen(rd())
{
    n=num;
    sum=0;
    eps=1e-8;
    dstore=new double[n];
    int i;
    sq=(int)(ceil(cbrt(n))+eps);
    sqn1=(int)(ceil(1.0*n/sq)+eps);
    sqn2=(int)(ceil(1.0*sqn1/sq)+eps);
    tdstore=new double[sqn1];
    thdstore=new double[sqn2];
    int tei=0,ted=0,tei2=0,ted2=0;
    double te=0,te2=0;
    for(i=0;i<n;i++)
    {
        dstore[i]=p[i];
        sum+=p[i];
        te+=p[i];
        tei++;
        if(tei==sq)
        {
            tdstore[ted]=te;
            te2+=te;
            te=0;
            tei=0;
            ted++;
            tei2++;
        }
        if(tei2==sq)
        {
            thdstore[ted2]=te2;
            te2=0;
            tei2=0;
            ted2++;
        }
    }
    if(tei!=0)tdstore[ted]=te,te2+=te,tei2+=1;
    if(tei2!=0)thdstore[ted2]=te2;
}

threedSample::~threedSample()
{
    delete [] dstore;
    delete [] tdstore;
    delete [] thdstore;
}

const double* threedSample::table1()
{
    return dstore;
}

const double* threedSample::table2()
{
    return tdstore;
}

const double* threedSample::table3()
{
    return thdstore;
}

double threedSample::resum()
{
    return sum;
}

void threedSample::change(int index,double weight)
{
    int row=index/sq/sq;
    thdstore[row]-=dstore[index];
    thdstore[row]+=weight;
    row=index/sq;
    tdstore[row]-=dstore[index];
    tdstore[row]+=weight;
    sum-=dstore[index];
    sum+=weight;
    dstore[index]=weight;
}

int threedSample::ransample()
{
    uniform_real_distribution<double> dr(0,sum);
    double dart=dr(gen);
    int row=0;
    while(thdstore[row]<dart)dart-=thdstore[row],row++;
    row*=sq;
    while(tdstore[row]<dart)dart-=tdstore[row],row++;
    row*=sq;
    while(dstore[row]<dart)dart-=dstore[row],row++;
    return row;
}
