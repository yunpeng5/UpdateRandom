#include "distributionSpeedTest.h"
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
#include <vector>
using namespace std;

int main()
{
    int k;
    cout<<"input 0 for one distribution test, 1 for multiple distribution test"<<endl;
    cin>>k;
    distributionSpeedTest a(k);
    aliasMethodFactory af;
    a.addmethod(&af,"Alias Method");
    stdDiscreteFactory st;
    a.addmethod(&st,"C++11 random number generator");
    snaiveSampleFactory sn;
    a.addmethod(&sn,"Naive searching");
    naiveSampleFactory ns;
    a.addmethod(&ns,"Naive searching with binary search.");
    twodNaiveFactory tn;
    a.addmethod(&tn,"Two-dimensional searching");
    threedSampleFactory ths;
    a.addmethod(&ths,"Three-dimensional searching");
    treeSampleFactory ts;
    a.addmethod(&ts,"Max-dimensional searching");
    randomNaiveFactory rn;
    a.addmethod(&rn,"Bounded distribution method");
    randomCateFactory cr;
    a.addmethod(&cr,"Bounded distribution method with group 0");
    refinedRandomFactory rr;
    a.addmethod(&rr,"Flat method");
    starFactory str;
    a.addmethod(&str,"Star method");
    heapSampleFactory hpr;
    a.addmethod(&hpr,"Heap method");
    a.distest();
    return 0;
}
