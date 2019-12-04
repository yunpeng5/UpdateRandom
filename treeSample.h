#ifndef MtreeSample
#define MtreeSample

#include "baseDiscrete.h"

#include <random>
using namespace std;

class treeSample:public baseDiscrete
{
public:
    //create the table
    treeSample(int num,double p[]);
    //delete the table
    ~treeSample();
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
    double *tdstore;
};

#endif // MtreeSample
