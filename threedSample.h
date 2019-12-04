#ifndef MthreedSample
#define MthreedSample

#include "baseDiscrete.h"

#include <random>
using namespace std;

class threedSample:public baseDiscrete
{
public:
    //create the table
    threedSample(int num,double p[]);
    //delete the table
    ~threedSample();
    //random generate
    int ransample();
    //return the table
    const double* table1();
    const double* table2();
    const double* table3();
    double resum();
    //change the distribution
    void change(int index,double weight);
private:
    int n,sq,sqn1,sqn2;
    random_device rd;
    mt19937 gen;
    double sum,eps;
    double *dstore;
    double *tdstore;
    double *thdstore;
};

#endif // MthreedSample
