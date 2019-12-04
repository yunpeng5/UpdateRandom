#ifndef MrefinedRandom
#define MrefinedRandom

#include "baseDiscrete.h"
#include <vector>
#include <random>
using namespace std;

class refinedRandom:public baseDiscrete
{
public:
    //create the table
    refinedRandom(int num,double p[]);
    //delete the table
    ~refinedRandom();
    //random generate
    int ransample();
    //change the distribution
    void change(int index,double weight);
private:
    int n,key,cn,maxlen;
    random_device rd;
    mt19937 gen;
    const double eps=1e-8;
    double maxweight=10002,sall;
    vector<vector<int> > cate;
    double* scate;
    double* prob;
    double* bound;
    vector<vector<int> > posi;
    int deci(double w);
};

#endif // MrefinedRandom
