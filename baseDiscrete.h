#ifndef MbaseDiscrete
#define MbaseDiscrete

class baseDiscrete
{
public:
    //using for starting generating method
    virtual ~baseDiscrete()=0;
    //using for giving the generating result
    virtual int ransample()=0;
    //using for change the distribution
    virtual void change(int index,double weight)=0;
};

inline baseDiscrete::~baseDiscrete(){};

#endif // MbaseDiscrete
