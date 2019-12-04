#ifndef MstdDiscrete
#define MstdDiscrete

#include "baseDiscrete.h"

#include <random>
using namespace std;

class stdDiscrete:public baseDiscrete
{
public:
    //start discrete distribution
    stdDiscrete(int num,double *w);
    //end discrete distribution
    ~stdDiscrete();
    //randomly generate
    int ransample();
    //change the distribution
    void change(int index,double weight);
private:
    int n;
    int flag;
    random_device rd;
    mt19937 gen;
    discrete_distribution<> d;
    double *dstore;
};

#endif // MstdDiscrete
