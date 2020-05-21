////
//// Created by 任玉双 on 2020/5/19.
////
//
//#include <iostream>
//
//
//using namespace std;
//
//struct inflatable {
//    string name;
//    float volume;
//    double trice;
//} mr_smith{
//        "name",
//        1.1,
//        2.2
//}, ms_ones;
//
//
//enum spectrum {
//    red, blue, green, orange
//};
//
//
//int main() {
//
//    spectrum band;
//    band = blue;
////    band = 2000; // 枚举变量只能使用自己定义的值
//
////    band = 1;// 枚举变量不能自动转为整型
//    int color = 1 + band; // 但是可以当成整型进行运算
//
//    band = spectrum(3);// 可以进行强制类型转换赋值给band类型
//
//    inflatable guest = {
//            "renyushuang",
//            1.88,
//            29.99,
//    };
//
//    enum bits {
//        one = 1,
//        two = 2,
//        four = 5
//    };
//    bits my_flag;
//    // 这个虽然没有具体定义，bits中最小值是1，最大值是10，6是在其中的所以合理
//    my_flag = bits(111111112);
//    cout << "my_flag = " << my_flag << endl;
//
//
//    cout << "mr_smith.name = " << mr_smith.name << endl;
//    cout << "mr_smith.volume = " << mr_smith.volume << endl;
//    cout << "mr_smith.trice = " << mr_smith.trice << endl;
//
//    // c++11 结构初始化方式
//    inflatable mayor = {
//    };
//    cout << "mayor.name = " << mayor.name << endl;
//    cout << "mayor.volume = " << mayor.volume << endl;
//    cout << "mayor.trice = " << mayor.trice << endl;
//    inflatable duck{
//            "renyushuang",
//            1.88,
//            29.99,
//    };
//
//    inflatable choice;
//    choice = duck;
//
//    struct position {
//        int x;
//        int y;
//    };
//
//    position gifts[2] = {
//            {1, 2},
//            {3, 4}
//    };
//    gifts[0].x;
//
//    // 1.字段的类型应为整型或枚举类型
//    // 2.冒号后面指定了位数
//    // 3.每个成员都被称为 字段
//    struct torgle_register {
//        unsigned int SN: 4;
//        unsigned int : 4; // 这种没有名称的 提供间距
//        bool goodIn: 1;
//        bool goodleTorgle: 1;
//    };
//    torgle_register x = {4, true, false};
//
//    // 共同体能存储不同的类型，但是只能同时存储一种类型
//    union une4all {
//        int int_val;
//        long long_val;
//        double double_val;
//    };
//    une4all une4all1 = {};
////    une4all1.int_val = 2;
//    une4all1.long_val = 2;
////    une4all1.double_val = 1.0;
//
//
//    cout << "une4all1.double_val = " << une4all1.double_val << endl;
//    cout << "une4all1.long_val = " << une4all1.long_val << endl;
//    cout << "une4all1.int_val = " << une4all1.int_val << endl;
//
//
//    return 0;
//}
//
//
