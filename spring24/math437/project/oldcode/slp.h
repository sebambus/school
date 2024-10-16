#include "matrix.h"
typedef vector<double> dvector;

class slp {
private:
    vector<double> in, mid, out;
    int inc, midc, outc;
    matrix w1, w2;
    vector<double> b1, b2;
public:
    slp(int, int, int);
    void transform();
    void initrandom(double,double,double,double);
    void setin(dvector);
    dvector getout();
    void fit(dvector,double);
};
