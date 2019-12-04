#ifndef MrandomCate
#define MrandomCate

#include "baseDiscrete.h"

#include <random>
using namespace std;

class randomCate:public baseDiscrete
{
public:
    //create the table
    randomCate(int num,double p[]);
    //delete the table
    ~randomCate();
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
    uniform_real_distribution<double> dr;
    double* prob;
    int* posi;
    int nzn;
    int* rposi;
    double maxn;
};

#endif // MrandomCate
