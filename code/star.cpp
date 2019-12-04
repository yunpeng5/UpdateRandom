#include "star.h"

#include <cmath>
#include <iostream> //debug
#include <assert.h>
using namespace std;

star::star(int num,double p[]) : gen(rd())
{
    n=num;
    sum=0;
    eps=1e-6;
    queue<Range*> Q;
    location.assign(n,make_pair(nullptr,-1));
    int i;
    for(i=0;i<n;i++)
    {
        sum+=p[i];
        int j=decide_range(p[i]);
        bool found=false;
        Range* rj=find_range(j,1,found);
        insert_bucket(i,p[i],rj);
        if(!found)Q.push(rj);
    }
    construct_level(1,Q);
}

star::~star()
{
    for(auto level : levelTable)
    {
        for(auto rj : level)
        {
            delete rj.second;
        }
    }
}

star::Range::Range(int number):rangeNumber(number),sum(0),location(make_pair(nullptr,-1)){}

star::Range* star::find_range(int base,int level,bool &found)
{
    if(levelTable.size()<level)levelTable.push_back(unordered_map<int,Range*>());
    auto findBase=levelTable[level-1].find(base);
    if(findBase==levelTable[level-1].end())
    {
        found=false;
        Range* newRange=new Range(base);
        levelTable[level-1][base]=newRange;
        return newRange;
    }
    else
    {
        found=true;
        return findBase->second;
    }
}

void star::insert_bucket(int source,double weight,Range* destination)
{
    destination->p.push_back(weight);
    destination->index.push_back(source);
    location[source].first=destination;
    location[source].second=destination->p.size()-1;
    destination->sum+=weight;
}

void star::insert_bucket(Range* source,Range* destination)
{
    destination->subLevel.push_back(source);
    destination->sum+=source->sum;
    source->location.first=destination;
    source->location.second=destination->subLevel.size()-1;
}

void star::construct_level(int level,queue<Range*> &Q)
{
    levelSum.push_back(0);
    levelRoot.push_back(0);
    queue<Range*> Q1;
    bool more_than_one=false;
    while(!Q.empty())
    {
        Range* ri=Q.front();
        Q.pop();
        double wi=ri->sum;
        if(ri->p.size()+ri->subLevel.size()>1)
        {
            int j=decide_range(wi);
            bool found=false;
            Range* rj=find_range(j,level+1,found);
            if(!found)Q1.push(rj);
            insert_bucket(ri,rj);
            //levelTable[level-1].erase(levelTable[level-1].find(ri->rangeNumber));
            more_than_one=true;
        }
        else
        {
            levelSum[level-1]+=wi;
            levelRoot[level-1]|=decide_root(ri->rangeNumber);
        }
    }
    if(more_than_one)construct_level(level+1,Q1);
}

void star::change(int index,double weight)
{
    //showTable();
    Range* rj=location[index].first;
    int loc=location[index].second;
    double oriWeight=rj->p[loc];
    sum-=oriWeight;
    deleteWeight(rj,loc,oriWeight,1);
    //showTable();
    //consistent();
    int j=decide_range(weight);
    bool found;
    Range* newRj=find_range(j,1,found);
    insert_bucket(index,weight,newRj);
    sum+=weight;
    addWeight(newRj,1);
    //showTable();
    //consistent();
}

void star::deleteWeight(Range* rj,int loc,double oriWeight,int level)
{
    assert(rj!=nullptr&&loc>=0&&oriWeight+eps>=0&&level>=1&&rj->sum+eps>=0);
    rj->sum-=oriWeight;

    if(level==1)
    {
        rj->p[loc]=rj->p[rj->p.size()-1];
        rj->p.pop_back();
        rj->index[loc]=rj->index[rj->index.size()-1];
        rj->index.pop_back();
        location[rj->index[loc]].second=loc;
        if(rj->index.size()==0)
        {
            levelTable[level-1].erase(levelTable[level-1].find(rj->rangeNumber));
            levelSum[level-1]-=oriWeight;
            levelRoot[level-1]&=~(decide_root(rj->rangeNumber));
            assert(levelSum[level-1]+eps>=0&&levelRoot[level-1]+eps>=0);
        }
    }
    else
    {
        rj->subLevel[loc]=rj->subLevel[rj->subLevel.size()-1];
        rj->subLevel[loc]->location.second=loc;
        rj->subLevel.pop_back();
        if(rj->subLevel.size()==0)
        {
            levelTable[level-1].erase(levelTable[level-1].find(rj->rangeNumber));
            levelSum[level-1]-=oriWeight;
            levelRoot[level-1]&=~(decide_root(rj->rangeNumber));
            assert(levelSum[level-1]+eps>=0&&levelRoot[level-1]+eps>=0);
        }
    }
    
    if(rj->location.first!=nullptr)deleteWeight(rj->location.first,rj->location.second,rj->sum+oriWeight,level+1);

    if(rj->index.size()+rj->subLevel.size()==0)
    {
        delete rj;
    }
    else if(rj->index.size()+rj->subLevel.size()==1)
    {
        assert(rj->sum+eps>=0);
        levelSum[level-1]+=rj->sum;
        levelRoot[level-1]|=decide_root(rj->rangeNumber);
        rj->location.first=nullptr;
        rj->location.second=-1;
    }
    else if(rj->index.size()+rj->subLevel.size()>1)
    {
        int j=decide_range(rj->sum);
        bool found=false;
        Range* nextRj=find_range(j,level+1,found);
        insert_bucket(rj,nextRj);
        addWeight(nextRj,level+1);
    }      
}

void star::addWeight(Range* rj,int level)
{
    int childNum=rj->index.size()+rj->subLevel.size();
    assert(childNum>=1);
    if(childNum==1)
    {
        if(levelSum.size()<level)
        {
            levelSum.push_back(0);
            levelRoot.push_back(0);
        }
        assert(levelSum.size()>=level);
        levelSum[level-1]+=rj->sum;
        levelRoot[level-1]|=decide_root(rj->rangeNumber);
    }
    else if(childNum==2)
    {
        double makeup=rj->index.size()==0?rj->subLevel[rj->subLevel.size()-1]->sum:rj->p[rj->p.size()-1];
        levelSum[level-1]-=rj->sum-makeup;
        levelRoot[level-1]&=~(decide_root(rj->rangeNumber));
        int j=decide_range(rj->sum);
        bool found=false;
        Range* nextRj=find_range(j,level+1,found);
        insert_bucket(rj,nextRj);
        addWeight(nextRj,level+1);
    }
    else
    {
        assert(rj->location.first!=nullptr);
        double makeup=rj->index.size()==0?rj->subLevel[rj->subLevel.size()-1]->sum:rj->p[rj->p.size()-1];
        deleteWeight(rj->location.first,rj->location.second,rj->sum-makeup,level+1);
        int j=decide_range(rj->sum);
        bool found=false;
        Range* nextRj=find_range(j,level+1,found);
        insert_bucket(rj,nextRj);
        addWeight(nextRj,level+1);
    }
}

int star::ransample()
{
    uniform_real_distribution<> U(0,sum);
    double cum=0,dart=U(gen);
    int i;
    for(i=0;i<levelSum.size();i++)
    {
        cum+=levelSum[i];
        if(cum>dart)
        {
            dart-=(cum-levelSum[i]);
            cum=0;
            break;
        }
    }
    unsigned long long root=levelRoot[i];
    Range* rj;
    while(1)
    {
        //cout<<"!"<<root<<endl;
        if(root>=4294967296)
        {
            int base=(int)(floor(log2(root>>32)));
            rj=levelTable[i].find(base)->second;
            dart-=rj->sum;
            if(dart<0.1)break;
            root&=~(1ull<<(32+base));
        }
        else
        {
            int base=(int)(floor(log2(root)));
            rj=levelTable[i].find(base-32)->second;
            dart-=rj->sum;
            if(dart<0.1)break;
            root&=~(1ull<<base);
        }
    }
    while(1)
    {
        if(rj->index.size()!=0)
        {
            double bound=1<<abs(rj->rangeNumber);
            if(rj->rangeNumber<0)bound=1.0/bound;
            uniform_int_distribution<> I(0,rj->index.size()-1);
            uniform_real_distribution<> R(0.0,1.0);
            while(1)
            {
                dart=I(gen);
                double pr=R(gen);
                //cout<<"*"<<bound<<" "<<rj->p[dart]<<" "<<pr<<endl;
                if(pr<rj->p[dart]/bound)return rj->index[dart];
            }
        }
        else
        {
            double bound=1<<abs(rj->rangeNumber);
            if(rj->rangeNumber<0)bound=1.0/bound;
            uniform_int_distribution<> I(0,rj->subLevel.size()-1);
            uniform_real_distribution<> R(0.0,1.0);
            while(1)
            {
                dart=I(gen);
                double pr=R(gen);
                //cout<<"?"<<bound<<" "<<rj->subLevel[dart]->sum<<" "<<pr<<endl;
                if(pr<rj->subLevel[dart]->sum/bound)
                {
                    rj=rj->subLevel[dart];
                    break;
                }
            }
        }
    }
}

void star::showTable()
{
    int i;
    cout<<"total sum:"<<sum<<endl;
    for(i=0;i<levelTable.size();i++)
    {
        cout<<"level "<<i+1<<" sum "<<levelSum[i]<<" root "<<levelRoot[i]<<endl;
        for(auto rj : levelTable[i])
        {
            cout<<"range number: "<<rj.second->rangeNumber<<" sum: "<<rj.second->sum<<" parent: ";
            if(rj.second->location.first==nullptr)cout<<"null"<<endl;
            else cout<<rj.second->location.first->rangeNumber<<endl;
            cout<<"containing:"<<endl;
            if(rj.second->subLevel.size()!=0){for(auto rjc : rj.second->subLevel)cout<<rjc->sum<<" ";cout<<endl;}
            else {for(auto rjc : rj.second->p)cout<<rjc<<" ";cout<<endl;}
        }
    }
    cout<<"\n"<<endl;
}

int star::consistent()
{
    double sumCount=0;
    int i,j;
    for(i=0;i<levelTable.size();i++)
    {
        sumCount+=levelSum[i];
        double lSum=0;
        unsigned long long lRoot=0;
        //double lRoot=0;
        for(auto rj : levelTable[i])
        {
            if(rj.second->location.first==nullptr)
            {
                lSum+=rj.second->sum;
                lRoot|=decide_root(rj.second->rangeNumber);
                //double rootAdd=
            }
            double rSum=0;
            for(j=0;j<rj.second->subLevel.size();j++)
            {
                rSum+=rj.second->subLevel[j]->sum;
                assert(rj.second->subLevel[j]->location.first==rj.second&&rj.second->subLevel[j]->location.second==j);
                assert(decide_range(rj.second->subLevel[j]->sum)==rj.second->rangeNumber);
            }
            for(j=0;j<rj.second->p.size();j++)
            {
                rSum+=rj.second->p[j];
                assert(location[rj.second->index[j]].first==rj.second);
                assert(decide_range(rj.second->p[j])==rj.second->rangeNumber);
            }
            assert(fabs(rSum-rj.second->sum)<eps);
        }
        assert(fabs(lSum-levelSum[i])<eps);
        assert(lRoot==levelRoot[i]);
    }
    assert(fabs(sum-sumCount)<eps);
}

inline int star::decide_range(double p)
{
    return min(max((int)(floor(log2(p)))+1,-32),31);
}

inline unsigned long long star::decide_root(int rangeNumber)
{
    return 1ull<<(rangeNumber+32);
}