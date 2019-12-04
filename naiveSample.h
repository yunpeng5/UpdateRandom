#ifndef MnaiveSample
#define MnaiveSample

#include "baseDiscrete.h"

#include <random>
using namespace std;

class naiveSample:public baseDiscrete
{
public:
    //create the table
    naiveSample(int num,double p[]);
    //delete the table
    ~naiveSample();
    //random generate
    int ransample();
    //return the table
    const double* table();
    //change the distribution
    void change(int index,double weight);
private:
    int n,flag;
    random_device rd;
    mt19937 gen;
    double* prob;
    double sum;
    void init();
    double *dstore;
};

#endif // MnaiveSample
