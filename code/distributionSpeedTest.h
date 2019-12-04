#ifndef MdistributionSpeedTest
#define MdistributionSpeedTest

#include <vector>
#include <string>
using namespace std;

#include "dsFactory.h"

class distributionSpeedTest
{
public:
    distributionSpeedTest(int t);
    void distest();
    void addmethod(dsFactory *fa,string s);
    const vector<vector<double> > table();
private:
    int type,nofm;
    vector<vector<double> > onedisdata;
    vector<dsFactory*> flist;
    vector<string> namelist;
    vector<string> onestring;
    vector<string> mulstring;
    int msize;
    void randomp(vector<double> &a,int dv,int ad,int le);
    void randomp(double *p,int dv,int ad,int le);
    void zrandomp(vector<double> &a);
    void frandomp(vector<double> &a);
    void fzrandomp(double *p,int le);
    void nfrandomp(double *p,int le);
    void hfrandom(double *p,int le);
};

#endif // MdistributionSpeedTest
