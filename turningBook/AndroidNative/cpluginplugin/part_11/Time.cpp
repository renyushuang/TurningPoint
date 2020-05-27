//
// Created by 任玉双 on 2020/5/26.
//

#include "Time.h"

Time Time::operator+(const Time &time) {
    Time sum;
    sum.minutes = this->minutes + time.minutes;
    sum.hours = this->hours + time.hours + sum.minutes / 60;
    sum.minutes % 60;
    return sum;
}

Time::Time(int h, int m) {

}

Time operator*(double m, const Time &time) {
    return Time();
}

Time::Time() {

}
