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
#include "dsFactory.h"
#include "baseDiscrete.h"

#include <iostream>
#include <cstdio>
#include <chrono>
#include <vector>
#include <random>
#include <cstdlib>
using namespace std;

vector<dsFactory*> flist;
vector<string> namelist;
int msize=0;

int sizeBegin,sizeEnd,sizeStep;
int ratioBegin,ratioEnd,ratioStep;
int sampleBegin,sampleEnd,sampleStep;
int distributionSelect;
int timeSelect,tme1,tme2,timeRepeat;
int maxWeight;
int ratioreverse;

void addmethod(dsFactory *fa,string s)
{
    flist.push_back(fa);
    namelist.push_back(s);
    msize++;
}

void baseRandom(double p[],int n)
{
    int i;
    for(i=0;i<n;i++)p[i]=rand()%maxWeight;
}

void largeRangeFloatRandom(double p[],int n)
{
    int i;
    for(i=0;i<n;i++)p[i]=1.0*(rand()%1000000)/(rand()%1000000+1);
}

int randomCheck(double p[],int n)
{
    int i;
    for(i=0;i<n;i++)if(p[i]!=0)return 0;
    return 1;
}

int randomChangeCheck(double p[],int n,int cn,double cweight)
{
    if(cweight!=0)return 0;
    int i;
    for(i=0;i<n;i++)if(i!=cn&&p[i]!=0)return 0;
    return 1;
}

int test(double p[],int n,int ratio,int sampleTime)
{
    int ratioR=1;
    if(ratioreverse==1)
    {
        ratioR=ratioEnd-ratio+ratioBegin;
        ratio=1;
    }
    chrono::time_point<chrono::system_clock> timeStart,timeEnd;
    chrono::duration<double> elapsedSeconds;
    int i,j,k,winner=-1;
    double wintime;
    for(i=0;i<msize;i++)
    {
        int tle=0;
        timeEnd=timeStart;
        elapsedSeconds=timeEnd-timeStart;
        timeStart = chrono::system_clock::now();
        baseDiscrete* ob=flist[i]->create(n,p);
        ob->ransample();
        timeEnd = chrono::system_clock::now();
        elapsedSeconds += timeEnd-timeStart;
        for(j=0;j<sampleTime;j++)
        {
            //int cn=rand()%n,cweight=rand()%maxWeight;
            //while(randomChangeCheck(p,n,cn,cweight))cn=rand()%n,cweight=rand()%maxWeight;
            for(k=0;k<ratio;k++)
            {
                int cn=-1;
                double cweight=-1;
                if(distributionSelect==0)do{cn=rand()%n;cweight=rand()%maxWeight;}while(randomChangeCheck(p,n,cn,cweight));
                else if(distributionSelect==1)do{cn=rand()%n;cweight=1.0*(rand()%1000000)/(rand()%1000000+1);}while(randomChangeCheck(p,n,cn,cweight));
                timeStart = chrono::system_clock::now();
                ob->change(cn,cweight);
                timeEnd = chrono::system_clock::now();
                elapsedSeconds += timeEnd-timeStart;
            }
            for(k=0;k<ratioR;k++)
            {
                timeStart = chrono::system_clock::now();
                ob->ransample();
                timeEnd = chrono::system_clock::now();
                elapsedSeconds += timeEnd-timeStart;
            }
            if(elapsedSeconds.count()>1){tle=1;break;}
        }
        delete ob;
        if(tle==0)if(winner==-1||elapsedSeconds.count()<wintime)winner=i,wintime=elapsedSeconds.count();
        //cout<<i+1<<" "<<elapsedSeconds.count()<<endl;
    }
    return winner;
}

double testTime(double p[],int n,int ratio,int sampleTime)
{
    chrono::time_point<chrono::system_clock> timeStart,timeEnd;
    chrono::duration<double> elapsedSeconds;
    int i,j,k,rp;
    int me1=tme1-1,me2=tme2-1;
    double time1=0,time2=0;
    for(rp=0;rp<timeRepeat;rp++)
    for(i=0;i<msize;i++)
    {
        if(i!=me1&&i!=me2)continue;
        timeEnd=timeStart;
        elapsedSeconds=timeEnd-timeStart;
        timeStart = chrono::system_clock::now();
        baseDiscrete* ob=flist[i]->create(n,p);
        ob->ransample();
        timeEnd = chrono::system_clock::now();
        elapsedSeconds += timeEnd-timeStart;
        for(j=0;j<sampleTime;j++)
        {
            //int cn=rand()%n,cweight=rand()%maxWeight;
            //while(randomChangeCheck(p,n,cn,cweight))cn=rand()%n,cweight=rand()%maxWeight;
            for(k=0;k<ratio;k++)
            {
                int cn=-1;
                double cweight=-1;
                if(distributionSelect==0)do{cn=rand()%n;cweight=rand()%maxWeight;}while(randomChangeCheck(p,n,cn,cweight));
                else if(distributionSelect==1)do{cn=rand()%n;cweight=1.0*(rand()%1000000)/(rand()%1000000+1);}while(randomChangeCheck(p,n,cn,cweight));
                timeStart = chrono::system_clock::now();
                ob->change(cn,cweight);
                timeEnd = chrono::system_clock::now();
                elapsedSeconds += timeEnd-timeStart;
            }
            timeStart = chrono::system_clock::now();
            ob->ransample();
            timeEnd = chrono::system_clock::now();
            elapsedSeconds += timeEnd-timeStart;
        }
        delete ob;
        if(i==me1)time1+=elapsedSeconds.count();
        if(i==me2)time2+=elapsedSeconds.count();
        //cout<<i+1<<" "<<elapsedSeconds.count()<<endl;
    }
    return (time1-time2)/timeRepeat;
}

void draw()
{
    int i,j,k;
    for(i=ratioEnd;i>=ratioBegin;i-=ratioStep)
    {
        for(j=sizeBegin;j<=sizeEnd;j+=sizeStep)
        {
            for(k=sampleBegin;k<=sampleEnd;k+=sampleStep)
            {
                int n=j;
                double p[n];
                if(distributionSelect==0)do{baseRandom(p,n);}while(randomCheck(p,n));
                else if(distributionSelect==1)do{largeRangeFloatRandom(p,n);}while(randomCheck(p,n));
                //for(int de=0;de<n;de++)cout<<p[de]<<" ";cout<<endl;
                if(timeSelect==0)
                {
                    int winner=test(p,n,i,k);
                    cout<<winner+1<<"\t";
                }
                else if(timeSelect==1)
                {
                    double timeSub=testTime(p,n,i,k);
                    cout<<timeSub<<"\t";
                }
            }
        }
        cout<<endl;
    }
}

int main()
{
    setbuf(stdout,NULL);
    random_device rd;
    srand(rd());
    aliasMethodFactory af;
    addmethod(&af,"Alias Method");
    stdDiscreteFactory st;
    addmethod(&st,"C++11 random number generator");
    snaiveSampleFactory sn;
    addmethod(&sn,"Naive searching");
    naiveSampleFactory ns;
    addmethod(&ns,"Naive searching with binary search.");
    twodNaiveFactory tn;
    addmethod(&tn,"Two-dimensional searching");
    threedSampleFactory ths;
    addmethod(&ths,"Three-dimensional searching");
    treeSampleFactory ts;
    addmethod(&ts,"Max-dimensional searching");
    randomNaiveFactory rn;
    addmethod(&rn,"Bounded distribution method");
    randomCateFactory cr;
    addmethod(&cr,"Bounded distribution method with group 0");
    refinedRandomFactory rr;
    addmethod(&rr,"Flat method");

    sizeBegin=1,sizeEnd=2001,sizeStep=50;
    ratioBegin=1801,ratioEnd=2001,ratioStep=50;
    sampleBegin=5000,sampleEnd=5000,sampleStep=100;
    distributionSelect=1;
    timeSelect=0,tme1=8,tme2=0,timeRepeat=5;
    maxWeight=10001;
    ratioreverse=1;
    draw();

    return 0;
}
