#include "twodNaive.h"

#include <cmath>
using namespace std;

twodNaive::twodNaive(int num,double p[]) : gen(rd())
{
    n=num;
    sum=0;
    eps=1e-8;
    dstore=new double[n];
    int i;
    sq=(int)(ceil(sqrt(n))+eps);
    sqn=(int)(ceil(1.0*n/sq)+eps);
    tdstore=new double[sqn];
    int tei=0,ted=0;
    double te=0;
    for(i=0;i<n;i++)
    {
        dstore[i]=p[i];
        sum+=p[i];
        te+=p[i];
        tei++;
        if(tei==sq)
        {
            tdstore[ted]=te;
            te=0;
            tei=0;
            ted++;
        }
    }
    if(tei!=0)tdstore[ted]=te;
}

twodNaive::~twodNaive()
{
    delete [] dstore;
    delete [] tdstore;
}

const double* twodNaive::table1()
{
    return dstore;
}

const double* twodNaive::table2()
{
    return tdstore;
}

double twodNaive::resum()
{
    return sum;
}

void twodNaive::change(int index,double weight)
{
    int row=index/sq;
    tdstore[row]-=dstore[index];
    tdstore[row]+=weight;
    sum-=dstore[index];
    sum+=weight;
    dstore[index]=weight;
}

int twodNaive::ransample()
{
    uniform_real_distribution<double> dr(0,sum);
    double dart=dr(gen);
    int row=0;
    while(tdstore[row]<dart)dart-=tdstore[row],row++;
    row*=sq;
    while(dstore[row]<dart)dart-=dstore[row],row++;
    return row;
}
