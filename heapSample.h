#ifndef MheapSample
#define MheapSample

#include "baseDiscrete.h"

#include <random>
using namespace std;

class heapSample:public baseDiscrete
{
public:
    //create the table
    heapSample(int num,double p[]);
    //delete the table
    ~heapSample();
    //random generate
    int ransample();
    //print the table
    void showTable();
    //change the distribution
    void change(int index,double weight);
    //check consistency
    int consistent();
private:
    class Node
    {
    public:
        double val;
        double lSum;
        double rSum;
        int index;
        bool operator < (const Node& rhs) const 
        {
            return val > rhs.val; //max come first
        }
    };
    int parent(int i) { return (i-1)/2; }
    int left(int i) { return (2*i + 1); }
    int right(int i) { return (2*i + 2); }
    int n;
    random_device rd;
    mt19937 gen;
    double sum,eps;
    Node *harr;
    int *position;
};

#endif // MheapSample
