#ifndef MaliasMethod
#define MaliasMethod

#include "baseDiscrete.h"

#include <random>
using namespace std;

class aliasMethod:public baseDiscrete
{
public:
    //create the prob and alias table
    aliasMethod(int num,double p[]);
    //delete two table
    ~aliasMethod();
    //randomly generate
    int ransample();
    //return table alias
    const int *tableAlias();
    //return table prob
    const double *tableProb();
    //change the distribution
    void change(int index,double weight);
private:
    int n,flag;
    random_device rd;
    mt19937 gen;
    uniform_int_distribution<int> d;
    uniform_real_distribution<double> dr;
    int *alias;
    double *prob;
    void init();
    double *dstore;
};

#endif // MaliasMethod
