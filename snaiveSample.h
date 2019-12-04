#ifndef MsnaiveSample
#define MsnaiveSample

#include "baseDiscrete.h"
#include <random>
using namespace std;

class snaiveSample:public baseDiscrete
{
public:
    //create the table
    snaiveSample(int num,double p[]);
    //delete the table
    ~snaiveSample();
    //random generate
    int ransample();
    //return the table
    const double* table();
    //change the distribution
    void change(int index,double weight);
private:
    int n;
    random_device rd;
    mt19937 gen;
    double* prob;
    double sum;
};

#endif // MsnaiveSample
