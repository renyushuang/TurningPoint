//
// Created by 任玉双 on 2020/5/19.
//

#include <iostream>


using namespace std;

struct inflatable {
    string name;
    float volume;
    double trice;
} mr_smith{
        "name",
        1.1,
        2.2
}, ms_ones;

int main() {

    inflatable guest = {
            "renyushuang",
            1.88,
            29.99,
    };

    cout << "mr_smith.name = " << mr_smith.name << endl;
    cout << "mr_smith.volume = " << mr_smith.volume << endl;
    cout << "mr_smith.trice = " << mr_smith.trice << endl;

    // c++11 结构初始化方式
    inflatable mayor = {
    };
    cout << "mayor.name = " << mayor.name << endl;
    cout << "mayor.volume = " << mayor.volume << endl;
    cout << "mayor.trice = " << mayor.trice << endl;
    inflatable duck{
            "renyushuang",
            1.88,
            29.99,
    };

    inflatable choice;
    choice = duck;

    struct position {
        int x;
        int y;
    };

    position gifts[2] = {
            {1, 2},
            {3, 4}
    };
    gifts[0].x;

    // 1.字段的类型应为整型或枚举类型
    // 2.冒号后面指定了位数
    // 3.每个成员都被称为 字段
    struct torgle_register {
        unsigned int SN: 4;
        unsigned int : 4; // 这种没有名称的 提供间距
        bool goodIn: 1;
        bool goodleTorgle: 1;
    };
    torgle_register x = {4, true, false};

    // 共同体能存储不同的类型，但是只能同时存储一种类型
    union une4all {
        int int_val;
        long long_val;
        double double_val;
    };
    une4all une4all1 = {};
    une4all1.int_val = 2;
    une4all1.long_val = 2;
    une4all1.double_val = 1.0;


    cout << "une4all1.double_val = " << une4all1.double_val << endl;
    cout << "une4all1.long_val = " << une4all1.long_val << endl;
    cout << "une4all1.int_val = " << une4all1.int_val << endl;


    return 0;
}


