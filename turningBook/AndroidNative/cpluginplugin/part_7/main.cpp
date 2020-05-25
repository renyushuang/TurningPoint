#include <iostream>

using namespace std;

void simple();

double cube(double);

void estimate(int lines, double (*pt)(double));

int main() {

    double (*pf)(double);
    pf = cube;

//    estimate(1, pf);

    // 指针调用
    double x = (*pf)(1);
    cout << "x = " << x << endl;
//    simple();
//
//    double side = 10;
//    cube(side);
//    cout << "resut side = " << side << endl;


    typedef double real;

    return 0;
}


int sum_arr(int *arr[], int n) {
    int totle = 0;
    for (int i = 0; i < n; i++) {
        totle = totle + (*arr)[i];
    }

    return totle;
}


double cube(double side) {
    side = side + 1;
    cout << "cube side = " << side << endl;
    return side;
}


void simple() {
    cout << "I'm but a simple function. \n";

}