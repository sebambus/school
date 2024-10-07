#include <fstream>
#include <vector>
using namespace std;
typedef vector<double> dvector;
typedef vector<vector<double>> ddvector;

int sizeofcsv(char* filename) {
    FILE* in = fopen(filename, "r");
    int count = 0;
    char* sink = new char[128];
    while(fscanf(in, "%s\n", sink) == 1) {
        count++;
    }
    return count;
}

double** csvtoarray(char* filename) {
    FILE* in = fopen(filename, "r");

    char* sink = new char[128];
    fscanf(in, "%s\n", sink); 

    int size = sizeofcsv(filename);
    double** data = new double*[size];
    for(int i = 0; i < size; i++) {
        data[i] = new double[3];
        fscanf(in, "%lf,%lf,%lf\n", &data[i][0], &data[i][1], &data[i][2]);
    }
    return data;
}

ddvector csvtoddvector(char* filename) {
    FILE* in = fopen(filename, "r");

    char* sink = new char[128];
    fscanf(in, "%s\n", sink);

    int size = sizeofcsv(filename);
    ddvector data(size);
    for(int i = 0; i < size; i++) {
        data[i] = dvector(3);
        fscanf(in, "%lf,%lf,%lf\n", &data[i][0], &data[i][1], &data[i][2]);
    }
    return data;
}