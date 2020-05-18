//
// Created by 任玉双 on 2020/5/17.
//
#include <iostream>

using namespace std;

int main() {

    int hats = 10, heads = 5;

    cout << "hats + heads = " << hats + heads << endl;
    cout << "hats - heads = " << hats - heads << endl;
    cout << "hats * heads = " << hats * heads << endl;
    cout << "hats / heads = " << hats / heads << endl;
    // 取余数
    cout << "hats % heads = " << hats % heads << endl;


    9/5; // int除法
    9L/5L; // Long除法
    9.0/5.0;//double除法
    9.0f/5.0f; // float除法

    const int Lbs_per_stn = 14;
    int lbs = 34;

    int stone = lbs/Lbs_per_stn;
    int pounds = lbs%Lbs_per_stn;
    cout<<stone<<" stone "<<pounds<<" pounds"<<endl;

    long a = 111;
    int b = a;

    auto n = 100;// n为int
    auto x = 1.5;// x为double
    auto y = 1.3e12L;// y为long double

    return 0;
}
