#include "lazyAliasMethod.h"

#include <queue>
#include <vector>
#include <iostream>
using namespace std;

lazyAliasMethod::lazyAliasMethod(int num,double p[]) : gen(rd()), d(0,num-1), dr(0.0,1.0)
{
    dstore.assign(num,0);
    alias.assign(num,0);
    prob.assign(num,0);
    for(int i=0;i<num;i++)dstore[i]=p[i];
    n=num;
    init();
}

void lazyAliasMethod::init()
{
    missProb=0;
    queue<int> small;
    queue<int> large;
    double p[n];
    int i;
    sum=0;
    for(i=0;i<n;i++)sum+=dstore[i];
    for(i=0;i<n;i++)
    {
        p[i]=dstore[i]*n/sum;
        if(p[i]<1)small.push(i);
        else large.push(i);
    }
    while((!small.empty())&&(!large.empty()))
    {
        //cout<<small.size()<<" "<<large.size()<<endl;
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

lazyAliasMethod::~lazyAliasMethod()
{

}

int lazyAliasMethod::ransample()
{
    while(true){
        int sel=d(gen);
        double sel2=dr(gen);
        if(sel2<prob[sel]){
            return sel;
        }
        else{
            if(alias[sel]!=-1)return alias[sel];
        }
    }
}

const vector<int>& lazyAliasMethod::tableAlias()
{
    return alias;
}

const vector<double>& lazyAliasMethod::tableProb()
{
    return prob;
}

void lazyAliasMethod::change(int index,double weight)
{
    dstore[index]=weight;
    init();
    return;
    double oriWeightScale=dstore[index]*n/sum;
    dstore[index]=weight;
    double weightScale=weight*n/sum;
    double diffWeightScale=oriWeightScale-weightScale;
    double newProb=prob[index]-diffWeightScale;
    if(alias[index]==-1&&newProb>0&&newProb<1){
        prob[index]=newProb;
    }
    else{
        init();
    }
}
