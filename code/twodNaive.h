#ifndef MtwodNaive
#define MtwodNaive

#include "baseDiscrete.h"

#include <random>
using namespace std;

class twodNaive:public baseDiscrete
{
public:
    //create the table
    twodNaive(int num,double p[]);
    //delete the table
    ~twodNaive();
    //random generate
    int ransample();
    //return the table
    const double* table1();
    const double* table2();
    double resum();
    //change the distribution
    void change(int index,double weight);
private:
    int n,sq,sqn;
    random_device rd;
    mt19937 gen;
    double sum,eps;
    double *dstore;
    double *tdstore;
};

#endif // MtwodNaive
