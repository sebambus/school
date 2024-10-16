#include <random>
#include <vector>
using namespace std;
typedef vector<double> dvector;
typedef vector<vector<double>> ddvector;

class matrix {
private:
    ddvector data;
public:
    matrix();
    matrix(ddvector);
    matrix(int,int,normal_distribution<double>);
    dvector multiply(dvector);
    void fit(dvector,dvector);
    matrix transpose();
};
