#ifndef MrandomNaive
#define MrandomNaive

#include "baseDiscrete.h"

#include <random>
using namespace std;

class randomNaive:public baseDiscrete
{
public:
    //create the table
    randomNaive(int num,double p[]);
    //delete the table
    ~randomNaive();
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
    uniform_int_distribution<int> d;
    uniform_real_distribution<double> dr;
    double* prob;
    double maxn;
};

#endif // MrandomNaive
