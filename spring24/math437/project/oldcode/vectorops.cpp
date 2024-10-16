#include <math.h>
#include <iostream>
#include <vector>
#include <cfloat>
using namespace std;
typedef vector<double> dvector;

void add(dvector &v1, dvector v2) {
    if(v1.size() != v2.size()) {
        cerr << "Unmatched sizes of added vectors (" << v1.size() << " != " << v2.size() << ")" << endl;
        exit(1);
    }
	for(int i = 0; i < v1.size(); i++)
		v1[i] = v1[i] + v2[i];
}

void subtract(dvector &v1, dvector v2) {
    if(v1.size() != v2.size()) {
        cerr << "Unmatched sizes of subtracted vectors (" << v1.size() << " != " << v2.size() << ")" << endl;
        exit(1);
    }
	for(int i = 0; i < v1.size(); i++)
		v1[i] -= v2[i];
}

double dot(dvector v1, dvector v2) {
    if(v1.size() != v2.size()) {
        cerr << "Unmatched sizes of dotted vectors (" << v1.size() << " != " << v2.size() << ")" << endl;
        exit(1);
    }
    double x = 0;
    for(int i = 0; i < v1.size(); i++)
        x += v1[i] * v2[i];
    return x;
}

void multbyterm(dvector &v1, dvector v2) {
    if(v1.size() != v2.size()) {
        cerr << "Unmatched sizes of term multiplied vectors (" << v1.size() << " != " << v2.size() << ")" << endl;
        exit(1);
    }
	for(int i = 0; i < v1.size(); i++)
		v1[i] = v1[i] * v2[i];
}

void scale(dvector &v, double n) {
	for(int i = 0; i < v.size(); i++)
		v[i] *= n;
}

void normalize(dvector& v) {
    double max, min = v[0];
    for(int i = 1; i < v.size(); i++) {
        if(v[i] > max) max = v[i];
        if(v[i] < min) min = v[i];
    }

    for(int i = 0; i < v.size(); i++) {
        v[i] -= min;
        v[i] /= max - min;
    }
}

void sigmoid(dvector &v) {
    for(int i = 0; i < v.size(); i++)
        v[i] = 1 / (1 + exp(-v[i]));
}

void fastsigmoid(dvector &v) {
    for(int i = 0; i < v.size(); i++)
        v[i] = v[i] / (1 + abs(v[i]));
}

void invfastsigmoid(dvector &v) {
    for(int i = 0; i < v.size(); i++)
        v[i] = v[i] / (1 - abs(v[i]));
}

void fastsigmoidscaled(dvector &v) {
    for(int i = 0; i < v.size(); i++)
        v[i] = (v[i] / (1 + abs(v[i])) + 1) / 2;

}
