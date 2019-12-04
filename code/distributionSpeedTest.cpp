#include "distributionSpeedTest.h"
#include "dsFactory.h"
#include "baseDiscrete.h"

#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <random>
#include <chrono>
using namespace std;

void distributionSpeedTest::randomp(vector<double> &a,int dv,int ad,int le)
{
    a.clear();
    int i;
    for(i=0; i<le; i++)a.push_back(rand()%dv+ad);
}

void distributionSpeedTest::randomp(double *p,int dv,int ad,int le)
{
    int i;
    for(i=0; i<le; i++)p[i]=rand()%dv+ad;
}

void distributionSpeedTest::frandomp(vector<double> &a)
{
    a.clear();
    int le=361;
    int i;
    for(i=0; i<le; i++)a.push_back(1.0*(rand()%1000000)/(rand()%1000000+1));
}

void distributionSpeedTest::zrandomp(vector<double> &a)
{
    a.clear();
    int le=361;
    int i;
    for(i=0; i<le; i++)if(rand()%5==0)a.push_back(rand()%1000000);
        else a.push_back(0);
}

void distributionSpeedTest::fzrandomp(double *p,int le)
{
    int i;
    for(i=0;i<le;i++)if(rand()%5==0)p[i]=rand()%10001;//1.0*(rand()%1000000)/(rand()%1000000+1);
    else p[i]=0;
}

void distributionSpeedTest::nfrandomp(double *p,int le)
{
    int i;
    for(i=0;i<le;i++)p[i]=1.0*rand()/RAND_MAX*10000;
}

void distributionSpeedTest::hfrandom(double *p,int le)
{
    int i;
    for(i=0;i<le;i++)p[i]=1.0*(rand()%1000000)/(rand()%1000000+1);
}

distributionSpeedTest::distributionSpeedTest(int t)
{
    random_device rd;
    srand(rd());
    type=t;
    msize=0;
    if(type==0)
    {
        onedisdata.push_back({4,3,2,2,1});
        onedisdata.push_back({0,4,3,0,0,2,2,0,1,0});
        vector<double> tem;
        randomp(tem,4,1,361);
        onedisdata.push_back(tem);
        randomp(tem,5,0,361);
        onedisdata.push_back(tem);
        randomp(tem,10001,0,361);
        onedisdata.push_back(tem);
        randomp(tem,1000001,0,361);
        onedisdata.push_back(tem);
        frandomp(tem);
        onedisdata.push_back(tem);
        zrandomp(tem);
        onedisdata.push_back(tem);

        onestring.push_back("1. Basic one distribution {4,3,2,2,1} with 10^7 sampling.");
        onestring.push_back("2. One distribution with some 0s {0,4,3,0,0,2,2,0,1,0} with 10^7 sampling.");
        onestring.push_back("3. One distribution whose length is 361 filled with random weight from 1 to 4 with 10^7 sampling.");
        onestring.push_back("4. One distribution whose length is 361 filled with random weight from 0 to 4 with 10^7 sampling.");
        onestring.push_back("5. One distribution whose length is 361 filled with random weight from 0 to 10000 with 10^7 sampling.");
        onestring.push_back("6. One distribution whose length is 361 filled with random weight from 0 to 1000000 with 10^7 sampling.");
        onestring.push_back("7. One distribution whose length is 361 filled with random weight (the weight is made from an integer divided by another to be float) from 0 to 1000000 with 10^7 sampling.");
        onestring.push_back("8. One distribution whose length is 361 filled with random weight from 0 to 1000000\n(there are about 4/5 of the weights are 0) with 10^7 sampling.");
    }
}

void distributionSpeedTest::distest()
{
    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> elapsed_seconds;
    if(type==0)
    {
        const int testtime=1e7;
        cout<<"One distribution with multiple sampling test:"<<endl;
        int i,j,k;
        for(i=0; i<(int)onedisdata.size(); i++)
        {
            cout<<onestring[i]<<endl;
            int le=(int)onedisdata[i].size();
            double tcase[le];
            for(k=0;k<le;k++)tcase[k]=onedisdata[i][k];
            for(j=0; j<msize; j++)
            {
                start = chrono::system_clock::now();
                baseDiscrete* ob=flist[j]->create(le,tcase);
                for(k=0;k<testtime;k++)ob->ransample();
                delete ob;
                end = chrono::system_clock::now();
                elapsed_seconds = end-start;
                cout<<namelist[j]<<" test: "<<elapsed_seconds.count()<<"s"<<endl;
            }
            cout<<endl;
        }
    }
    if(type==1)
    {
        chrono::time_point<chrono::system_clock> start, end;
        chrono::duration<double> elapsed_seconds;
        start=chrono::system_clock::now();
        int i,j;
        /*
        cout<<"1. Basic 100000 total different distribution (each one has one sampling, the length of the weight array is 361 and the weights are from 0 to 100)"<<endl;
        for(i=0;i<msize;i++)
        {
            double p[361];
            int psize=361;
            end=start;
            elapsed_seconds=end-start;
            for(j=0;j<100000;j++)
            {
                randomp(p,101,0,psize);
                start = chrono::system_clock::now();
                baseDiscrete* ob=flist[i]->create(psize,p);
                ob->ransample();
                delete ob;
                end = chrono::system_clock::now();
                elapsed_seconds += end-start;
            }
            cout<<namelist[i]<<" test: "<<elapsed_seconds.count()<<"s"<<endl;
        }*/
        cout<<"2. Basic choose one weight in the array and change its value."<<endl;
        for(i=0;i<msize;i++)
        {
            double p[361];
            int psize=361;
            end=start;
            elapsed_seconds=end-start;
            randomp(p,10001,0,psize);
            start = chrono::system_clock::now();
            baseDiscrete* ob=flist[i]->create(psize,p);
            ob->ransample();
            end = chrono::system_clock::now();
            elapsed_seconds += end-start;
            for(j=0;j<100000;j++)
            {
                start = chrono::system_clock::now();
                ob->change(rand()%psize,rand()%10001);
                ob->ransample();
                end = chrono::system_clock::now();
                elapsed_seconds += end-start;
            }
            delete ob;
            cout<<namelist[i]<<" test: "<<elapsed_seconds.count()<<"s"<<endl;
        }
        cout<<endl;

        cout<<"2.5 weights from 0 to 5."<<endl;
        for(i=0;i<msize;i++)
        {
            double p[361];
            int psize=361;
            end=start;
            elapsed_seconds=end-start;
            randomp(p,6,0,psize);
            start = chrono::system_clock::now();
            baseDiscrete* ob=flist[i]->create(psize,p);
            ob->ransample();
            end = chrono::system_clock::now();
            elapsed_seconds += end-start;
            for(j=0;j<100000;j++)
            {
                start = chrono::system_clock::now();
                ob->change(rand()%psize,rand()%6);
                ob->ransample();
                end = chrono::system_clock::now();
                elapsed_seconds += end-start;
            }
            delete ob;
            cout<<namelist[i]<<" test: "<<elapsed_seconds.count()<<"s"<<endl;
        }
        cout<<endl;

        cout<<"3. Basic choose three weights in the array and change their value."<<endl;
        for(i=0;i<msize;i++)
        {
            double p[361];
            int psize=361;
            end=start;
            elapsed_seconds=end-start;
            randomp(p,10001,0,psize);
            start = chrono::system_clock::now();
            baseDiscrete* ob=flist[i]->create(psize,p);
            ob->ransample();
            end = chrono::system_clock::now();
            elapsed_seconds += end-start;
            for(j=0;j<100000;j++)
            {
                start = chrono::system_clock::now();
                ob->change(rand()%psize,rand()%10001);
                ob->change(rand()%psize,rand()%10001);
                ob->change(rand()%psize,rand()%10001);
                ob->ransample();
                end = chrono::system_clock::now();
                elapsed_seconds += end-start;
            }
            delete ob;
            cout<<namelist[i]<<" test: "<<elapsed_seconds.count()<<"s"<<endl;
        }
        cout<<endl;

        cout<<"4. Basic choose one weight to change under condition that the array contains 4/5 0s"<<endl;
        for(i=0;i<msize;i++)
        {
            double p[361];
            int psize=361;
            end=start;
            elapsed_seconds=end-start;
            fzrandomp(p,psize);
            start = chrono::system_clock::now();
            baseDiscrete* ob=flist[i]->create(psize,p);
            ob->ransample();
            end = chrono::system_clock::now();
            elapsed_seconds += end-start;
            for(j=0;j<100000;j++)
            {
                start = chrono::system_clock::now();
                int te=0;
                if(rand()%5==0)te=rand()%10001;
                ob->change(rand()%psize,te);//1.0*(rand()%1000000)/(rand()%1000000+1));
                ob->ransample();
                end = chrono::system_clock::now();
                elapsed_seconds += end-start;
            }
            delete ob;
            cout<<namelist[i]<<" test: "<<elapsed_seconds.count()<<"s"<<endl;
        }
        cout<<endl;

        cout<<"5. Basic choose one weight to change under condition that weights are float"<<endl;
        for(i=0;i<msize;i++)
        {
            double p[361];
            int psize=361;
            end=start;
            elapsed_seconds=end-start;
            //fzrandomp(p,psize);
            //hfrandom(p,psize);
            for(int dei=0;dei<psize;dei++)if(1.0*rand()/RAND_MAX>0.98)p[dei]=9000+1.0*rand()/RAND_MAX*1000;
            else p[dei]=1.0*rand()/RAND_MAX*50;
            start = chrono::system_clock::now();
            baseDiscrete* ob=flist[i]->create(psize,p);
            ob->ransample();
            end = chrono::system_clock::now();
            elapsed_seconds += end-start;
            int tle=0;
            for(j=0;j<100000;j++)
            {
                start = chrono::system_clock::now();
                double te;
                //if(rand()%5!=0)te=1.0*(rand()%1000000)/(rand()%1000000+1);
                //else te=rand()%1000000;
                //te=1.0*(rand()%1000000)/(rand()%1000000+1);
                if(1.0*rand()/RAND_MAX>0.98)te=9000+1.0*rand()/RAND_MAX*1000;
                else te=1.0*rand()/RAND_MAX*5;
                //te=rand()%10;
                ob->change(rand()%psize,te);
                //ob->change(0,100000);
                ob->ransample();
                end = chrono::system_clock::now();
                elapsed_seconds += end-start;
                if(elapsed_seconds.count()>1){tle=1;break;}
            }
            delete ob;
            if(tle==0)cout<<namelist[i]<<" test: "<<elapsed_seconds.count()<<"s"<<endl;
            else cout<<namelist[i]<<" test: cannot finish in 1s"<<endl;
        }
        cout<<endl;

        cout<<"5.5 weights are normal float."<<endl;
        for(i=0;i<msize;i++)
        {
            double p[361];
            int psize=361;
            end=start;
            elapsed_seconds=end-start;
            nfrandomp(p,psize);
            start = chrono::system_clock::now();
            baseDiscrete* ob=flist[i]->create(psize,p);
            ob->ransample();
            end = chrono::system_clock::now();
            elapsed_seconds += end-start;
            int tle=0;
            for(j=0;j<100000;j++)
            {
                start = chrono::system_clock::now();
                ob->change(rand()%psize,1.0*rand()/RAND_MAX*10000);
                ob->ransample();
                end = chrono::system_clock::now();
                elapsed_seconds += end-start;
                if(elapsed_seconds.count()>1){tle=1;break;}
            }
            delete ob;
            if(tle==0)cout<<namelist[i]<<" test: "<<elapsed_seconds.count()<<"s"<<endl;
            else cout<<namelist[i]<<" test: cannot finish in 1s"<<endl;
        }
        cout<<endl;

        cout<<"6. Change the length of array to 2000"<<endl;
        for(i=0;i<msize;i++)
        {
            double p[2000];
            int psize=2000;
            end=start;
            elapsed_seconds=end-start;
            randomp(p,10001,0,psize);
            start = chrono::system_clock::now();
            baseDiscrete* ob=flist[i]->create(psize,p);
            ob->ransample();
            end = chrono::system_clock::now();
            elapsed_seconds += end-start;
            int tle=0;
            for(j=0;j<100000;j++)
            {
                start = chrono::system_clock::now();
                double te;
                //if(rand()%5!=0)te=1.0*(rand()%1000000)/(rand()%1000000+1);
                //else te=rand()%1000000;
                te=rand()%10001;
                //te=rand()%10;
                ob->change(rand()%psize,te);
                //ob->change(0,100000);
                ob->ransample();
                end = chrono::system_clock::now();
                elapsed_seconds += end-start;
                if(elapsed_seconds.count()>1){tle=1;break;}
            }
            delete ob;
            if(tle==0)cout<<namelist[i]<<" test: "<<elapsed_seconds.count()<<"s"<<endl;
            else cout<<namelist[i]<<" test: cannot finish in 1s"<<endl;
        }
        cout<<endl;

        cout<<"6.5 Change the length of array to 5"<<endl;
        for(i=0;i<msize;i++)
        {
            double p[5];
            int psize=5;
            end=start;
            elapsed_seconds=end-start;
            randomp(p,10001,0,psize);
            start = chrono::system_clock::now();
            baseDiscrete* ob=flist[i]->create(psize,p);
            ob->ransample();
            end = chrono::system_clock::now();
            elapsed_seconds += end-start;
            int tle=0;
            for(j=0;j<100000;j++)
            {
                start = chrono::system_clock::now();
                double te;
                //if(rand()%5!=0)te=1.0*(rand()%1000000)/(rand()%1000000+1);
                //else te=rand()%1000000;
                te=rand()%10001;
                //te=rand()%10;
                ob->change(rand()%psize,te);
                //ob->change(0,100000);
                ob->ransample();
                end = chrono::system_clock::now();
                elapsed_seconds += end-start;
                if(elapsed_seconds.count()>1){tle=1;break;}
            }
            delete ob;
            if(tle==0)cout<<namelist[i]<<" test: "<<elapsed_seconds.count()<<"s"<<endl;
            else cout<<namelist[i]<<" test: cannot finish in 1s"<<endl;
        }
        cout<<endl;

        cout<<"7. update whole data not reduce loop"<<endl;
        for(i=0;i<msize;i++)
        {
            double p[361];
            int psize=361;
            end=start;
            elapsed_seconds=end-start;
            randomp(p,10001,0,psize);
            start = chrono::system_clock::now();
            baseDiscrete* ob=flist[i]->create(psize,p);
            ob->ransample();
            end = chrono::system_clock::now();
            elapsed_seconds += end-start;
            int tle=0;
            for(j=0;j<100000;j++)
            {
                start = chrono::system_clock::now();
                for(int te=0;te<psize;te++)ob->change(te,rand()%10001);
                ob->ransample();
                end = chrono::system_clock::now();
                elapsed_seconds += end-start;
                //if(elapsed_seconds.count()>1){tle=1;break;}
            }
            delete ob;
            if(tle==0)cout<<namelist[i]<<" test: "<<elapsed_seconds.count()<<"s"<<endl;
            else cout<<namelist[i]<<" test: cannot finish in 1s"<<endl;
        }

        cout<<"8. more sampling per round"<<endl;
        for(i=0;i<msize;i++)
        {
            double p[361];
            int psize=361;
            end=start;
            elapsed_seconds=end-start;
            randomp(p,10001,0,psize);
            start = chrono::system_clock::now();
            baseDiscrete* ob=flist[i]->create(psize,p);
            ob->ransample();
            end = chrono::system_clock::now();
            elapsed_seconds += end-start;
            int tle=0;
            for(j=0;j<100000;j++)
            {
                start = chrono::system_clock::now();
                ob->change(rand()%psize,rand()%10001);
                int ter;
                for(ter=0;ter<15;ter++)ob->ransample();
                end = chrono::system_clock::now();
                elapsed_seconds += end-start;
                if(elapsed_seconds.count()>1){tle=1;break;}
            }
            delete ob;
            if(tle==0)cout<<namelist[i]<<" test: "<<elapsed_seconds.count()<<"s"<<endl;
            else cout<<namelist[i]<<" test: cannot finish in 1s"<<endl;
        }
    }
}

void distributionSpeedTest::addmethod(dsFactory *fa,string s)
{
    flist.push_back(fa);
    namelist.push_back(s);
    msize++;
}

const vector<vector<double> > distributionSpeedTest::table()
{
    return onedisdata;
}
