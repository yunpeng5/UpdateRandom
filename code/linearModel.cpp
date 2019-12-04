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
#include "stdDiscreteBoostFactory.h"
#include "dsFactory.h"
#include "baseDiscrete.h"

#include <iostream>
#include <cstdio>
#include <chrono>
#include <vector>
#include <random>
#include <fstream>
using namespace std;

double eps=1e-8;

vector<dsFactory*> flist;
vector<string> namelist;
int msize=0;

random_device rd;
mt19937 engine(rd());
uniform_int_distribution<int> d;

int Psize,genPer,upPer,avgOver;
int sampleRecord,sampleNow,sampleEnd,sampleChunk;
int distributionSelect;
int maxWeight;
vector<double> timeRecord;

ofstream output;

void addmethod(dsFactory *fa,string s)
{
    flist.push_back(fa);
    namelist.push_back(s);
    msize++;
}

void uniformReal(double p[],int n)
{
    int i;
    uniform_real_distribution<double> dr(0,maxWeight);
    for(i=0;i<n;i++)p[i]=dr(engine);
}

void uniformInt(int p[],int n)
{
    int i;
    uniform_int_distribution<int> dr(0,Psize-1);
    for(i=0;i<n;i++)p[i]=dr(engine);
}

void expReal(double p[],int n)
{
    int i;
    exponential_distribution<double> dr(0.001);
    for(i=0;i<n;i++)p[i]=min(dr(engine),10000.0);
}

//top 10% elements own 90% of total weights
void fewLarge(double p[],int n)
{
    uniform_real_distribution<double> group(0,1);
    for(int i=0;i<n;i++)
    {
        if(group(engine)<0.1)
        {
            uniform_real_distribution<double> dr(0,maxWeight);
            p[i]=dr(engine);
        }
        else
        {
            uniform_real_distribution<double> dr(0,maxWeight/81.0);
            p[i]=dr(engine);
        }
    }
}

int randomCheck(double p[],int n)
{
    int i;
    double sum=0;
    for(i=0;i<n;i++)sum+=p[i];
    if(sum<eps)return 0;
    return 1;
}

void draw(int mode,int num)
{
    int i,j,k;
    for(i=0;i<avgOver;i++)
    {
        int n=Psize;
        double p[n];
        if(distributionSelect==0)uniformReal(p,n);
        else if(distributionSelect==1) expReal(p,n);
        else if(distributionSelect==2) fewLarge(p,n);
        else return;

        chrono::time_point<chrono::high_resolution_clock> timeStart,timeEnd;
        chrono::duration<double> elapsedSeconds;
        timeEnd=timeStart;
        elapsedSeconds=timeEnd-timeStart;
        baseDiscrete* ob;

        if(mode==-1)
        {
            output<<0;
            for(j=0;j<sampleEnd/sampleRecord;j++)
            {
                timeStart = chrono::system_clock::now();
                for(k=0;k<sampleRecord;k++)
                {
                    ob=flist[num]->create(n,p); 
                }
                timeEnd = chrono::system_clock::now();
                elapsedSeconds += timeEnd-timeStart;
                output<<" "<<chrono::duration_cast<chrono::milliseconds>(elapsedSeconds).count();
            }
            output<<endl;
            continue;
        }
        else
        {
            timeStart = chrono::system_clock::now();
            ob=flist[num]->create(n,p);
            timeEnd = chrono::system_clock::now();
            elapsedSeconds += timeEnd-timeStart;
        }

        output<<chrono::duration_cast<chrono::microseconds>(elapsedSeconds).count();

        for(j=0;j<sampleEnd/sampleRecord;j++)
        {
            double changeW[sampleRecord];
            if(distributionSelect==0)uniformReal(changeW,sampleRecord);
            else if(distributionSelect==1) expReal(changeW,sampleRecord);
            else if(distributionSelect==2) fewLarge(changeW,sampleRecord);
            else return;
            int changeIndex[sampleRecord];
            uniformInt(changeIndex,sampleRecord);
            
            if(mode==0)
            {
                timeStart = chrono::system_clock::now();
                for(k=0;k<sampleRecord;k++)
                {
                    ob->ransample();
                }
                timeEnd = chrono::system_clock::now();
                elapsedSeconds += timeEnd-timeStart;
            }
            else if(mode==1)
            {
                timeStart = chrono::system_clock::now();
                for(k=0;k<sampleRecord;k++)
                {
                    ob->change(changeIndex[k],changeW[k]);
                }
                timeEnd = chrono::system_clock::now();
                elapsedSeconds += timeEnd-timeStart; 
            }
            else if(mode==2)
            {
                timeStart = chrono::system_clock::now();
                for(k=0;k<sampleRecord;k++)
                {
                    ob->change(changeIndex[k],changeW[k]);
                    ob->ransample();
                }
                timeEnd = chrono::system_clock::now();
                elapsedSeconds += timeEnd-timeStart;
            }
            output<<" "<<chrono::duration_cast<chrono::microseconds>(elapsedSeconds).count();
        }

        delete ob;
        output<<endl;
        cout<<i<<" finished"<<endl;
    }
}

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
    //randomCateFactory cr;
    //addmethod(&cr,"bound0");
    refinedRandomFactory rr;
    addmethod(&rr,"flat");
    starFactory str;
    addmethod(&str,"star");
    //heapSampleFactory hp;
    //addmethod(&hp,"heap");
    //stdDiscreteBoostFactory stbst;
    //addmethod(&stbst,"c11boost");

    Psize=-1,avgOver=3;
    sampleRecord=1e4,sampleNow=0,sampleEnd=1e6;
    distributionSelect=1;
    maxWeight=10000;
    int i;

    vector<int> sizelist({200,10, 11, 12, 13, 15, 16, 18, 19, 21, 24, 26, 29, 31, 35, 38, 42, 46, 51, 56, 61, 67, 74, 81, 90, 98, 108, 119, 131, 144, 159, 174, 192, 211, 232, 
+    255, 281, 309, 340, 374, 411, 453, 498, 548, 602, 663, 729, 802, 882, 970, 1067, 1174, 1291, 1420, 1562, 1719, 1891, 2080, 2288, 2516, 2768, 3045, 3349, 3684, 4053, 4458, 
+    4904, 5394, 5933, 6527, 7180, 7897, 8687, 9556, 10512, 11563, 12719, 13991, 15390, 16929, 18622, 20484, 22532, 24786, 27264, 29991});
    for(auto ni : sizelist)
    {
    Psize=ni;
    for(i=0;i<namelist.size();i++)
    {
        cout<<namelist[i]<<endl;
        output.open("./linear/result_"+namelist[i]+"_"+to_string(ni));
        int j;
        output<<0;
        for(j=1;j<=sampleEnd/sampleRecord;j++)output<<" "<<j*sampleRecord;output<<endl;
        //output<<"#building test"<<endl;
        //draw(-1,i);
        output<<"#sampling test"<<endl;
        draw(0,i);
        output<<"#sampling + updating test"<<endl;
        draw(2,i);
        output.close();
    }}
    return 0;
}
