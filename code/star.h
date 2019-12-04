#ifndef Mstar
#define Mstar

#include "baseDiscrete.h"

#include <random>
#include <queue>
#include <unordered_map>
using namespace std;

class star:public baseDiscrete
{
public:
    //create the table
    star(int num,double p[]);
    //delete the table
    ~star();
    //random generate
    int ransample();
    //show the level table, for debug
    void showTable();
    //change the distribution
    void change(int index,double weight);
private:
    class Range
    {
    public:
        Range(int number);
        int rangeNumber;
        double sum;
        vector<Range*> subLevel;
        vector<double> p;
        vector<int> index;
        pair<Range*,int> location;
    };
    Range* find_range(int base,int level,bool &found);
    void insert_bucket(int source,double weight,Range* destination);
    void insert_bucket(Range* source,Range* destination);
    void construct_level(int level,queue<Range*> &Q);
    void deleteWeight(Range* rj,int loc,double oriWeight,int level);
    void addWeight(Range* rj,int level);
    int consistent();
    int decide_range(double p);
    unsigned long long decide_root(int rangeNumber);
    int n;
    random_device rd;
    mt19937 gen;
    double sum,eps;
    vector<double> levelSum;
    vector<unsigned long long> levelRoot;
    vector<unordered_map<int,Range*>> levelTable;
    vector<pair<Range*,int>> location;
};

#endif // Mstar
