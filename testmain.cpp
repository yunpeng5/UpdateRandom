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
#include "starFactory.h"
#include "heapSampleFactory.h"
#include "stdDiscreteBoostFactory.h"
#include "lazyAliasMethodFactory.h"

#include <cmath>
#include <iostream>
#include <chrono>
#include <cassert>
#include <cstring>
#include <vector>
#include <fstream>

#include <random>
#include <cstdlib>
using namespace std;

mt19937 gen;

//Calculate the confidence interval for given possibility p
void confidenceInterval(double* p,double* ciup,double* cidown,int n,int testtime)
{
    double sum=0;
    double se[n];
    double pp[n];
    int i;
    for(i=0;i<n;i++)sum+=p[i];
    for(i=0;i<n;i++)pp[i]=p[i]/sum;
    for(i=0; i<n; i++)se[i]=1.96*sqrt(pp[i]*(1-pp[i])/testtime);
    for(i=0; i<n; i++)ciup[i]=pp[i]+se[i],cidown[i]=pp[i]-se[i];
}

//generate a random possibility array with length n
void randomp(double *p,int n)
{
    const int lmaxw=1000;
    const int maxw=100;
    int i;
    for(i=0; i<5; i++)
    {
        p[i]=rand()%lmaxw;
    }
    for(i=5; i<n; i++)
    {
        if(rand()%5!=0)p[i]=rand()%maxw;
        else p[i]=0;
    }
}

//general assert test
void asserttest(dsFactory *fa)
{
    for(int j=0;j<10;j++){
        int i;
        uniform_int_distribution<> de(10,30000);
        uniform_real_distribution<> dr(0,10000);
        int num=de(gen);
        double p[num];
        for(int i=0;i<num;i++)p[i]=dr(gen);
        baseDiscrete* ob=fa->create(num,p);
        uniform_int_distribution<> de2(0,num-1);
        for(i=0;i<num/2;i++){
            ob->change(de2(gen),dr(gen));
        }
        for(i=0;i<num;i++)
        {
            int te=ob->ransample();
            assert(te>=0);
            assert(te<num);
        }
        delete ob;
    }
}

//test generate method with one distribution, many sampling
void onedistest(dsFactory *fa,string name)
{
    cout<<"chi square test sampling"<<endl;
    const int testTime=1e7;
    uniform_int_distribution<> disUniInt(10,2000);
    uniform_real_distribution<> disUniReal(10,2000);
    //int n=disUniInt(gen);
    int n=1000;
    const int updateTime=n/2;
    vector<double> weight(n,0);
    double sum=0;
    for(int i=0;i<n;i++)weight[i]=disUniReal(gen);
    vector<double> oriWeight=weight;
    vector<int> updateIndex(updateTime,0);
    vector<double> updateWeight(updateTime,0);
    uniform_int_distribution<> disIndex(0,n-1);
    for(int i=0;i<updateTime;i++)
    {
        updateIndex[i]=disIndex(gen);
        updateWeight[i]=disUniReal(gen);
        weight[updateIndex[i]]=updateWeight[i];
    }
    for(int i=0;i<n;i++)sum+=weight[i];
    vector<double> expected(n,0);
    for(int i=0;i<n;i++)expected[i]=weight[i]/sum*testTime;
    vector<int> result(n,0);
    baseDiscrete* ob=fa->create(n,oriWeight.data());
    for(int i=0;i<updateTime;i++)ob->change(updateIndex[i],updateWeight[i]);
    for(int i=0;i<testTime;i++)
    {
        result[ob->ransample()]++;
    }
    delete ob;
    cout<<"test finished, write result to file"<<endl;
    ofstream output("chi_square_test",ofstream::app);
    output<<name<<endl;
    for(int i=0;i<result.size();i++)output<<result[i]<<" ";output<<endl;
    for(int i=0;i<expected.size();i++)output<<expected[i]<<" ";output<<endl;
    output.close();
    /*
    cout<<"multiple sampling test"<<endl;
    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> elapsed_seconds;
    randomp(p,n);
    int i,j;
    int re[n];
    memset(re,0,sizeof(re));
    double pre[n];
    double ciup[n];
    double cidown[n];
    const int overalltime=1000;
    const int testtime=10000;
    const int lmaxct=1000;
    const int chtime=n;
    int intervalfit[n];
    memset(intervalfit,0,sizeof(intervalfit));
    int ci[chtime];
    double ct[chtime];
    for(i=0;i<chtime;i++)ci[i]=rand()%n;
    for(i=0;i<chtime;i++)ct[i]=1.0*rand()/RAND_MAX*lmaxct;
    ct[chtime-1]=1e-5;
    ct[chtime-2]=1e-2;
    start = chrono::system_clock::now();
    baseDiscrete* ob=fa->create(n,p);
    for(i=0;i<chtime;i++)p[ci[i]]=ct[i];
    confidenceInterval(p,ciup,cidown,n,testtime);
    for(i=0;i<chtime;i++)ob->change(ci[i],ct[i]);
    for(i=0;i<overalltime;i++)
    {
        for(j=0;j<n;j++)re[j]=0;
        for(j=0;j<testtime;j++)
        {
            int te=ob->ransample();
            re[te]++;
        }
        for(j=0;j<n;j++)pre[j]=1.0*re[j]/testtime;
        for(j=0;j<n;j++)if(pre[j]>cidown[j]&&pre[j]<ciup[j])intervalfit[j]++;
    }
    delete ob;
    end = chrono::system_clock::now();
    elapsed_seconds = end-start;
    for(i=0;i<n;i++)if(100.0*intervalfit[i]/overalltime<90&&fabs(p[i]-0)>1e-6)cout<<"there are "<<100.0*intervalfit[i]/overalltime<<"% which fits "<<i<<" in ["<<
        cidown[i]<<" , "<<ciup[i]<<"] for "<<p[i]<<"\n";
    cout<< "elapsed time: " << elapsed_seconds.count() << "s"<<endl;*/
}

//test generate method with many distribution, many sampling
void muldistest(dsFactory *fa)
{
    cout<<"multiple distribution one sampling test"<<endl;
    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> elapsed_seconds;
    start=chrono::system_clock::now();
    end=start;
    elapsed_seconds=end-start;
    int n=250;
    double p[n];
    int i;
    const int testtime=100000;
    start = chrono::system_clock::now();
    randomp(p,n);
    baseDiscrete* ob=fa->create(n,p);
    ob->ransample();
    end = chrono::system_clock::now();
    elapsed_seconds+=end-start;
    for(i=0;i<testtime;i++)
    {
        int teindex=rand()%n;
        double teweight=rand()%1000;
        start = chrono::system_clock::now();
        ob->change(teindex,teweight);
        ob->ransample();
        end = chrono::system_clock::now();
        elapsed_seconds+=end-start;
    }
    start = chrono::system_clock::now();
    delete ob;
    end = chrono::system_clock::now();
    elapsed_seconds+=end-start;
    cout<< "elapsed time: " << elapsed_seconds.count() << "s"<<endl;
}

//test generate method with assert test, statistic test, speed test
void test(dsFactory *fa,string name)
{
    cout<<name<<endl;
    asserttest(fa);
    onedistest(fa,name);
    muldistest(fa);
    cout<<endl;
}

//-------------------------------------unit test---------------------------
//Check if all elements in alias table is as expected
void assertchecki(int *a,const int *b,int n)
{
    int i;
    for(i=0; i<n; i++)assert(a[i]==b[i]);
}

//Check if all elements in probability table is as expected
void assertcheckd(double *a,const double *b,int n)
{
    int i;
    for(i=0; i<n; i++)assert(fabs(a[i]-b[i])<1e-6);
}

void unittestalias(aliasMethodFactory *fa)
{
    int num=10;
    double p[10]={0,2,2,4,0,1.5,0,0,0.5,0};
    int sa[10]={1,3,3,0,2,3,3,5,1,2};
    double sp[10]={0,0.5,0,1,0,0.5,0,0,0.5,0};
    aliasMethod* ali=fa->create(num,p);
    const int* ta=ali->tableAlias();
    const double* tp=ali->tableProb();
    assertchecki(sa,ta,num);
    assertcheckd(sp,tp,num);
    num=10;
    int csa[]={0,0,3,0,5,0,0,3,0,3};
    double csp[]={1,0,0,1,0,0.5,0,0,0.5,0};
    ali->change(0,4);
    ali->change(1,0);
    ali->change(2,0);
    const int* cta=ali->tableAlias();
    const double* ctp=ali->tableProb();
    assertchecki(csa,cta,num);
    assertcheckd(csp,ctp,num);
    delete ali;
}

void unittestnaive(naiveSampleFactory *fa)
{
    int num=10;
    double p[]={0,2,2,4,0,1.5,0,0,0.5,0};
    naiveSample* nai=fa->create(num,p);
    const double* tprob=nai->table();
    double sprob[]={0,2,4,8,8,9.5,9.5,9.5,10,10};
    assertcheckd(sprob,tprob,num);
    num=10;
    nai->change(4,3);
    nai->change(5,0);
    const double* ct=nai->table();
    double cs[]={0,2,4,8,11,11,11,11,11.5,11.5};
    assertcheckd(cs,ct,num);
    delete nai;
}

void unittestsnaive(snaiveSampleFactory *fa)
{
    int num=10;
    double p[]={0,2,2,4,0,1.5,0,0,0.5,0};
    snaiveSample* nai=fa->create(num,p);
    const double* tprob=nai->table();
    double sprob[]={0,2,2,4,0,1.5,0,0,0.5,0};
    assertcheckd(sprob,tprob,num);
    num=10;
    nai->change(4,3);
    nai->change(5,0);
    const double* ct=nai->table();
    double cs[]={0,2,2,4,3,0,0,0,0.5,0};
    assertcheckd(cs,ct,num);
    delete nai;
}

void unittesttwod(twodNaiveFactory *fa)
{
    int num=23;
    double p[]={0,2,3,2,4,3,5,0,3,2,3,4,5,3,2,4,2,0,2,6,4,0,1};
    twodNaive* nai=fa->create(num,p);
    nai->change(0,1);
    nai->change(6,0);
    nai->change(21,2);
    nai->change(19,0);
    const double* ttable1=nai->table1();
    const double* ttable2=nai->table2();
    double tsum=nai->resum();
    double stable1[]={1,2,3,2,4,3,0,0,3,2,3,4,5,3,2,4,2,0,2,0,4,2,1};
    double stable2[]={12,8,17,8,7};
    double ssum=52;
    assertcheckd(stable1,ttable1,23);
    assertcheckd(stable2,ttable2,5);
    assert(fabs(ssum-tsum)<1e-6);
    delete nai;
}

void unitteststar(starFactory *fa)
{
    int n=10;
    double p[]={1/2.0,1/3.0,1/4.0,2,8,15,15,16,16,268};
    star* ob=fa->create(n,p);
    ob->showTable();
    delete ob;
    /*
    //int n=10;
    //double p[]={0,0,0,2,8,15,77,268,268,268};
    //double p[]={10000,0,0,2,8,15,0,268,268,268};
    //int n=6;
    //double p[]={3,3,3,3,6,6};
    int n=6;
    double p[]={3,3,3,3,6,0};
    int i,j;
    int re[n];
    memset(re,0,sizeof(re));
    double pre[n];
    double ciup[n];
    double cidown[n];
    const int overalltime=1000;
    const int testtime=10000;
    int intervalfit[n];
    memset(intervalfit,0,sizeof(intervalfit));
    star* ob=fa->create(n,p);
    ob->showTable();
    //ob->change(0,0);
    //ob->change(6,77);
    //p[0]=0;
    //p[6]=77;
    //ob->change(4,0);
    //p[4]=0;
    ob->change(5,6);
    p[5]=6;
    ob->showTable();
    confidenceInterval(p,ciup,cidown,n,testtime);
    for(i=0;i<overalltime;i++)
    {
        for(j=0;j<n;j++)re[j]=0;
        for(j=0;j<testtime;j++)
        {
            int te=ob->ransample();
            re[te]++;
        }
        for(j=0;j<n;j++)pre[j]=1.0*re[j]/testtime;
        for(j=0;j<n;j++)if(pre[j]>cidown[j]&&pre[j]<ciup[j])intervalfit[j]++;
    }
    delete ob;
    for(i=0;i<n;i++)if(100.0*intervalfit[i]/overalltime<90&&fabs(p[i]-0)>1e-6)cout<<"there are "<<100.0*intervalfit[i]/overalltime<<"% which fits "<<i<<" in ["<<
        cidown[i]<<" , "<<ciup[i]<<"] for "<<p[i]<<"\n";*/
}

void unitrandomn(randomNaiveFactory *fa)
{
    int num=10;
    double p[]={0,2,2,4,0,1.5,0,0,0.5,0};
    randomNaive* nai=fa->create(num,p);
    const double* tprob=nai->table();
    double sprob[]={0,2,2,4,0,1.5,0,0,0.5,0};
    assertcheckd(sprob,tprob,num);
    num=10;
    nai->change(4,3);
    nai->change(5,0);
    const double* ct=nai->table();
    double cs[]={0,2,2,4,3,0,0,0,0.5,0};
    assertcheckd(cs,ct,num);
    delete nai;
}

void unittree(treeSampleFactory *fa)
{
    int num=16;
    double p[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    treeSample* nai=fa->create(num,p);
    const double* tprob=nai->table();
    for(int i=0;i<4*num;i++)cout<<tprob[i]<<" ";cout<<endl;
    nai->change(15,1);
    tprob=nai->table();
    for(int i=0;i<4*num;i++)cout<<tprob[i]<<" ";cout<<endl;
    return;
    double sprob[]={0,2,2,4,0,1.5,0,0,0.5,0};
    assertcheckd(sprob,tprob,num);
    num=10;
    nai->change(4,3);
    nai->change(5,0);
    const double* ct=nai->table();
    double cs[]={0,2,2,4,3,0,0,0,0.5,0};
    assertcheckd(cs,ct,num);
    delete nai;
}

void unittesthp(heapSampleFactory *fa)
{
    int num=10;
    double p[]={0,2,3,2,4,3,5,0,3,2};
    heapSample* hp=fa->create(num,p);
    hp->showTable();
    hp->change(8,10);
    hp->showTable();
    delete hp;
}
//----------------------------------------------------------------------------

int main()
{
    random_device rd;
    gen.seed(rd());
    srand(rd());
    
    aliasMethodFactory alif;
    //unittestalias(&alif);
    test(&alif,"Alias Method");

    stdDiscreteFactory discf;
    test(&discf,"C++ GCC");

    stdDiscreteBoostFactory disbst;
    test(&disbst,"C++ Boost");

    naiveSampleFactory naive;
    //unittestnaive(&naive);
    test(&naive,"Binary Search");

    snaiveSampleFactory snaive;
    unittestsnaive(&snaive);
    test(&snaive,"Linear Search");

    twodNaiveFactory tnaive;
    unittesttwod(&tnaive);
    test(&tnaive,"Two Level Search");

    threedSampleFactory thsample;
    test(&thsample,"Three Level Search");

    randomNaiveFactory rnaive;
    unitrandomn(&rnaive);
    test(&rnaive,"Rejection Method");

    treeSampleFactory tsm;
    //unittree(&tsm);
    test(&tsm,"Binary Tree Search");

    refinedRandomFactory rrandom;
    //unittestrrandom(&rrandom);
    test(&rrandom,"Flat Method");

    randomCateFactory crandom;
    //unittestrrandom(&rrandom);
    test(&crandom,"Rejection Method without 0");
    
    starFactory strandom;
    //unitteststar(&strandom);
    test(&strandom,"Log* Method");

    heapSampleFactory hp;
    //unittesthp(&hp);
    test(&hp,"Heap Method");

    lazyAliasMethodFactory la;
    test(&la,"Lazy Alias Method");
    return 0;
}
