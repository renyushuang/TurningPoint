//
// Created by 任玉双 on 2020/5/26.
//

#ifndef PART_11_TIME_H
#define PART_11_TIME_H


#include <iosfwd>

class Time {
private:
    int hours;
    int minutes;

public:
    Time();

    Time(int h, int m = 0);

    Time operator+(const Time &time);

    //“虽然operator *( )函数是在类声明中声明的，但它不是成员函数，因此不能使用成员运算符来调用；
    //虽然operator *( )函数不是成员函数，但它与成员函数的访问权限相同。”
    friend Time operator*(double m, const Time &time);

//    friend void operator<<(std::ostream &os, const Time &time);
    friend std::ostream &operator<<(std::ostream &os, const Time &time);

    operator double();
};


#endif //PART_11_TIME_H
