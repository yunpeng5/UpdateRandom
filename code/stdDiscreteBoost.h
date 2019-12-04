#ifndef MstdDiscreteBoost
#define MstdDiscreteBoost

#include "baseDiscrete.h"

#include <boost/random.hpp>
#include <boost/random/random_device.hpp>
using namespace std;

class stdDiscreteBoost:public baseDiscrete
{
public:
    //start discrete distribution
    stdDiscreteBoost(int num,double *w);
    //end discrete distribution
    ~stdDiscreteBoost();
    //randomly generate
    int ransample();
    //change the distribution
    void change(int index,double weight);
private:
    int n;
    int flag;
    boost::random::random_device rd;
    boost::random::mt19937 gen;
    boost::random::discrete_distribution<> d;
    double *dstore;
};

#endif // MstdDiscreteBoost
