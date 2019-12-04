#ifndef MlazyAliasMethod
#define MlazyAliasMethod

#include "baseDiscrete.h"

#include <random>
#include <vector>
using namespace std;

class lazyAliasMethod:public baseDiscrete
{
public:
    //create the prob and alias table
    lazyAliasMethod(int num,double p[]);
    //delete two table
    ~lazyAliasMethod();
    //randomly generate
    int ransample();
    //return table alias
    const vector<int>& tableAlias();
    //return table prob
    const vector<double>& tableProb();
    //change the distribution
    void change(int index,double weight);
private:
    int n;
    random_device rd;
    mt19937 gen;
    uniform_int_distribution<int> d;
    uniform_real_distribution<double> dr;
    vector<int> alias;
    vector<double> prob;
    double sum;
    void init();
    vector<double> dstore;
    double missProb;
};

#endif // MlazyAliasMethod
