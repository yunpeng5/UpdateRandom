#include "aliasMethodFactory.h"
#include "stdDiscreteFactory.h"
#include "naiveSampleFactory.h"
#include "snaiveSampleFactory.h"
#include "twodNaiveFactory.h"
#include "threedSampleFactory.h"
#include "randomNaiveFactory.h"
#include "treeSampleFactory.h"
#include "refinedRandomFactory.h"
#include "randomCateFactory.h"
#include "starFactory.h"
#include "heapSampleFactory.h"
#include "dsFactory.h"
#include "baseDiscrete.h"

#include <iostream>
#include <cstdio>
#include <chrono>
#include <vector>
#include <random>
#include <fstream>
#include <cmath>
using namespace std;

double eps=1e-8;

vector<dsFactory*> flist;
vector<string> namelist;
int msize=0;

random_device rd;
mt19937 engine(rd());
uniform_int_distribution<int> d;

void addmethod(dsFactory *fa,string s)
{
    flist.push_back(fa);
    namelist.push_back(s);
    msize++;
}

void initBandit(double qstar[],int n)
{
    normal_distribution<double> dr(0,1);
    for(int i=0;i<n;i++)qstar[i]=min(max(dr(engine),-9.0),9.0);
}

int bestAction(double qstar[],int n)
{
    int a=0,p=qstar[0];
    for(int i=0;i<n;i++)
    {
        if(qstar[i]>p)p=qstar[i],a=i;
    }
    return a;
}

void showBandit(double qstar[],int n,int bestA)
{
    cout<<"size: "<<n<<endl;
    for(int i=0;i<n;i++)cout<<qstar[i]<<" ";cout<<endl;
    cout<<"best action: "<<bestA<<endl;
}

ofstream output;

int main()
{
    //setbuf(stdout,NULL);
    aliasMethodFactory af;
    addmethod(&af,"alias");
    stdDiscreteFactory st;
    addmethod(&st,"c11");
    snaiveSampleFactory sn;
    addmethod(&sn,"naive");
    naiveSampleFactory ns;
    addmethod(&ns,"binary");
    twodNaiveFactory tn;
    addmethod(&tn,"twod");
    threedSampleFactory ths;
    addmethod(&ths,"threed");
    treeSampleFactory ts;
    addmethod(&ts,"maxd");
    randomNaiveFactory rn;
    addmethod(&rn,"bound");
    randomCateFactory cr;
    addmethod(&cr,"bound0");
    refinedRandomFactory rr;
    addmethod(&rr,"flat");
    starFactory str;
    addmethod(&str,"star");
    heapSampleFactory hp;
    addmethod(&hp,"heap");

    int avgOver=10;
    //maxWeight=10000;
    //int i;

    vector<int> sizelist({200,10,30,50,70,90,100,300,500,700,900,1000,3000,5000,7000,9000,10000,20000,30000});
    

    //for(auto ni:sizelist){
    //    int n=ni;
    
        int n=10;
        double qstar[n];
        initBandit(qstar,n);
        int bestA=bestAction(qstar,n);
        showBandit(qstar,n,bestA);
        for(int m=0;m<msize;m++){
            int chooseBest=0;
            chrono::time_point<chrono::high_resolution_clock> timeStart,timeEnd;
            chrono::duration<double> elapsedSeconds;
            timeEnd=timeStart;
            elapsedSeconds=timeEnd-timeStart;
            for(int round=0;round<2000;round++){
                double qest[n];
                double expinit[n];
                int tried[n];
                for(int i=0;i<n;i++)qest[i]=0,tried[i]=0,expinit[i]=1;
                baseDiscrete* ob=flist[m]->create(n,expinit);
                timeStart = chrono::system_clock::now();
                for(int i=0;i<1e3;i++)
                {
                    //int a=choose_action(ob);
                    int a=ob->ransample();
                    //double r=give_reward(psatr,a);
                    normal_distribution<double> dr(qstar[a],1);
                    double r=min(max(dr(engine),-9.0),9.0);
                    tried[a]++;
                    qest[a]+=1.0/tried[a]*(r-qest[a]);
                    //cout<<exp(qest[a])<<endl;
                    ob->change(a,exp(qest[a]));
                }
                timeEnd = chrono::system_clock::now();
                elapsedSeconds += timeEnd-timeStart;
                if(ob->ransample()==bestA)chooseBest++;
                delete ob;
                //for(int i=0;i<n;i++)cout<<qest[i]<<" ";cout<<endl;
            }
            cout<<namelist[m]<<" "<<chrono::duration_cast<chrono::milliseconds>(elapsedSeconds).count()/2000.0<<endl;
            cout<<chooseBest/2000.0<<endl;
        }
    //}
    

    return 0;
}
