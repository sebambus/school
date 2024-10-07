#include "slp.h"
#include "vectorops.h"
#include <random>
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
typedef vector<double> dvector;

slp::slp(int inc, int midc, int outc) {
    this->inc = inc;
    this->midc = midc;
    this->outc = outc;

    in = dvector(inc);
    mid = dvector(midc);
    out = dvector(outc);
    
    b1 = dvector(midc);
    b2 = dvector(outc);
}

void slp::transform() {
    mid = w1.multiply(in);
    add(mid, b1);
    fastsigmoid(mid);
    out = w2.multiply(mid);
    add(out, b2);
}

void slp::initrandom(double wmean, double wstdv, double bmean, double bstdv) {
    std::random_device r;
    std::default_random_engine rgen(r());
    
    std::normal_distribution<double> wdist(wmean, wstdv);
    w1 = matrix(midc, inc, wdist);
    w2 = matrix(outc, midc, wdist);
    
    std::normal_distribution<double> bdist(bmean, bstdv);
    for(int i = 0; i < midc; i++)
        b1[i] = bdist(rgen);
    for(int i = 0; i < outc; i++)
        b2[i] = bdist(rgen);
}

void slp::setin(dvector in) {
    this->in = dvector(in);
}

dvector slp::getout() {
    return out;
}

void slp::fit(dvector data, double eta) {
    dvector costv(out);
    subtract(costv, data);
    scale(costv, eta);

    matrix invw2 = w2.transpose();
    dvector midcost = invw2.multiply(costv);
    invfastsigmoid(midcost);
    subtract(b2, costv);
    w2.fit(mid, costv);
    
    subtract(b1, midcost);
    w1.fit(mid, midcost);
}
