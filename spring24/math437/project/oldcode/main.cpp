#include "slp.h"
#include "csvtools.h"
#include "vectorops.h"
#include <iostream>
#include <fstream>
#include <random>
using namespace std;
typedef vector<double> dvector;
typedef vector<vector<double>> ddvector;

int main() {
    // FIT ANN TO INTERPOLATE TIME SERIES
    slp timeseries(1, 4, 2);
    timeseries.initrandom(0, 1, 0, 1);
    int datac = sizeofcsv("lynxhare.csv") - 1;
    ddvector data = csvtoddvector("lynxhare.csv");
    normalize(data[0]);
    
    for(int j = 0; j < 1000; j++) {
    for(int i = 0; i < datac; i++) {
        timeseries.setin(dvector(1, data[i][0]));
        timeseries.transform();
        timeseries.fit(dvector(data[i].begin() + 1, data[i].end()), 0.1);
    }
    }

    ofstream file;
    file.open("modlynxhare.csv");
    file << "Year,Hare,Lynx" << endl;
    for(int i = 1845; i < 1936; i++) {
        dvector n(1, i);
        timeseries.setin(n);
        timeseries.transform();
        dvector out = timeseries.getout();
        file << i << "," << out[0] << "," << out[1] << endl;
    }
    
    // TAKE DERIVATIVES OF NODE
    // FIT NODE TO DERIVATIVE
    slp node(2, 10, 2);
}
