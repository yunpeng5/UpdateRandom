#include "refinedRandom.h"

#include <vector>
#include <cmath>
#include <cassert>

//#define t_debug
using namespace std;

refinedRandom::refinedRandom(int num,double p[]) : gen(rd())
{
    n=num;
    posi.assign(n,vector<int>(2));
    prob=new double[n];
    key=2;
    cn=(int)(ceil(log(maxweight)/log(2))+eps)+1;
    cate.assign(cn,vector<int>());
    int i;
    //for(i=0;i<(int)cate.size();i++)cate[i].reserve(maxlen);
    scate=new double[cn];
    bound=new double[cn];
    bound[0]=1;
    for(i=1;i<cn;i++)bound[i]=bound[i-1]*key;
    sall=0;
    for(i=0;i<cn;i++)scate[i]=0;
    for(i=0;i<n;i++)
    {
        assert(p[i]<maxweight+eps);
        prob[i]=p[i];
        int t=deci(p[i]);
        cate[t].push_back(i);
        posi[i][0]=t;
        posi[i][1]=(int)cate[t].size()-1;
        scate[t]+=p[i];
        sall+=p[i];
    }
}

refinedRandom::~refinedRandom()
{
    delete [] prob;
    delete [] scate;
    delete [] bound;
}

int refinedRandom::deci(double w)
{
    if(w<1+eps)return 0;
    int te=(int)(log(w)/log(2)+eps)+1;
    assert(te>=0);
    assert(te<cn);
    return te;
}

int refinedRandom::ransample()
{
    int cdart=0,dart;
    uniform_real_distribution<double> dr(0,sall);
    double cpr=dr(gen);
    while(cate[cdart].size()==0||scate[cdart]<cpr){cpr-=scate[cdart],cdart++;}
    assert(cdart<cn);
    vector<int> &te=cate[cdart];
    int ten=(int)te.size();
    //if(ten==0)cout<<scate[cdart]<<" "<<cpr<<endl;
    double tem=bound[cdart];
    while(1)
    {
        uniform_int_distribution<int> d(0,ten-1);
        dart=d(gen);
        uniform_real_distribution<double> dr2(0,tem);
        double pr=dr2(gen);
        if(pr<prob[te[dart]])break;
    }
    return te[dart];
}

//find if it change category

//if no, change sum all
//change sum cate
//change weight

//push it into new group
//change sum all
//change sum cate
//switch last one in old category to its position
//erase last one in old cate
//change sum cate
//change sum all
//change posi
//change prob
void refinedRandom::change(int index,double weight)
{
    //if(prob[index]==0&&weight==0)return;
    if(deci(weight)==posi[index][0])
    {
        sall=sall-prob[index]+weight;
        int tepoi=posi[index][0];
        scate[tepoi]=scate[tepoi]-prob[index]+weight;
        prob[index]=weight;
    }
    else
    {
        int newc=deci(weight);
        int oldc=posi[index][0];
        int oldn=posi[index][1];
        cate[newc].push_back(index);
        sall+=weight;
        scate[newc]+=weight;

        vector<int> &teov=cate[oldc];
        teov[oldn]=teov[teov.size()-1];
        posi[teov[teov.size()-1]][1]=oldn;
        teov.pop_back();
        sall-=prob[index];
        scate[oldc]-=prob[index];

        prob[index]=weight;
        posi[index][0]=newc;
        posi[index][1]=(int)cate[newc].size()-1;
    }
}
