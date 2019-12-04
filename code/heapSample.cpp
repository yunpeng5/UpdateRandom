#include "heapSample.h"

#include <cmath>
#include <algorithm>
#include <iostream>
#include <assert.h>
using namespace std;

heapSample::heapSample(int num,double p[]) : gen(rd())
{
    random_device rd;
    srand(rd());
    n=num;
    sum=0;
    eps=1e-6;
    harr=new Node[n];
    position=new int[n];
    for(int i=0;i<n;i++)
    {
        harr[i].val=p[i];
        harr[i].lSum=0;
        harr[i].rSum=0;
        harr[i].index=i;
        sum+=p[i];
    }
    sort(harr,harr+n);
    for(int i=n-1;i>=0;i--)
    {
        if(left(i)<n)harr[i].lSum=harr[left(i)].lSum+harr[left(i)].rSum+harr[left(i)].val;
        if(right(i)<n)harr[i].rSum=harr[right(i)].lSum+harr[right(i)].rSum+harr[right(i)].val;
        position[harr[i].index]=i;
    }
}

heapSample::~heapSample()
{
    delete [] harr;
    delete [] position;
}

void heapSample::showTable()
{
    for(int i=0;i<n;i++)
    {
        cout<<"|| lSum: "<<harr[i].lSum<<" val: "<<harr[i].val<<" rSum: "<<harr[i].rSum<<" ";
        if(((i+2)&(i+2-1))==0)cout<<endl;
    }
    cout<<"\n"<<"********* position *********"<<endl;
    for(int i=0;i<n;i++)cout<<position[i]<<" ";cout<<endl;
}

int heapSample::consistent()
{
    for(int i=0;i<n;i++)
    {
        if(left(i)<n)assert(fabs(harr[i].lSum-(harr[left(i)].lSum+harr[left(i)].val+harr[left(i)].rSum))<eps);
        if(right(i)<n)assert(fabs(harr[i].rSum-(harr[right(i)].lSum+harr[right(i)].val+harr[right(i)].rSum))<eps);
    }
    int count[n];
    for(int i=0;i<n;i++)count[i]=0;
    double tsum=0;
    for(int i=0;i<n;i++)
    {
        assert(harr[position[i]].index==i);
        tsum+=harr[position[i]].val;
        count[position[i]]+=1;
        assert(count[position[i]]<=1);
    }
    assert(fabs(tsum-sum)<eps);
}

int heapSample::ransample()
{
    uniform_real_distribution<double> dr(0,sum);
    double dart=dr(gen);
    int i=0;
    while(1)
    {
        if(dart<harr[i].lSum)i=left(i);
        else if(dart<harr[i].lSum+harr[i].val)return harr[i].index;
        else
        {
            dart=dart-harr[i].lSum-harr[i].val;
            i=right(i);
        }
    }
    return -1;
}

void heapSample::change(int index,double weight)
{
    int i=position[index];
    sum=sum-harr[i].val+weight;
    harr[i].val=weight;
    while(i!=0&&harr[parent(i)].val<harr[i].val)
    {
        swap(harr[parent(i)].val,harr[i].val);
        swap(harr[parent(i)].index,harr[i].index);
        i=parent(i);
    }
    i=position[index];
    while(1)
    {
        position[harr[i].index]=i;
        if(i==0)break;
        int p=parent(i);
        if(i==p*2+1)harr[p].lSum=harr[i].lSum+harr[i].rSum+harr[i].val;
        else harr[p].rSum=harr[i].lSum+harr[i].rSum+harr[i].val;
        i=parent(i);
    }
    //consistent();
}
