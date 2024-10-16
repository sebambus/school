#include "matrix.h"
#include "vectorops.h"
#include <iostream>
using namespace std;

matrix::matrix() {
    matrix(ddvector(1, dvector(1, 0)));
}

matrix::matrix(ddvector data) {
    this->data = data;
}

matrix::matrix(int width, int height, std::normal_distribution<double> dist) {
    data = ddvector(width, dvector(height));

    std::random_device r;
    std::default_random_engine rgen(r());
    for(int i = 0; i < data.size(); i++)
        for(int j = 0; j < data[0].size(); j++)
            data[i][j] = dist(rgen);
}

dvector matrix::multiply(dvector v) {
    if(v.size() != data[0].size()) {
        cerr << "vector of size " << v.size() << " cannot be multiplied by a matrix of height " << data[0].size() << endl;
        exit(1);
    }
    dvector x(data.size());
    for(int i = 0; i < data.size(); i++)
        x[i] = dot(v, data[i]);
    return x;
}

void matrix::fit(dvector in, dvector out) {
    for(int i = 0; i < data.size(); i++)
        for(int j = 0; j < data[0].size(); j++)
            data[i][j] -= in[j] * out[i];
}

matrix matrix::transpose() {
    ddvector tdata(data[0].size(), dvector(data.size()));
    for(int i = 0; i < data.size(); i++)
        for(int j = 0; j < tdata.size(); j++)
            tdata[j][i] = data[i][j];
    matrix t(tdata);
    return t;
}
