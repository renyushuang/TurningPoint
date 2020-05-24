////
//// Created by 任玉双 on 2020/5/21.
////
//
//#include <iostream>
//
//using namespace std;
//
//int main() {
////    int dounts = 6;
////    cout << "&dounts = " << &dounts << endl;
//
//    int updates = 10;
//
//    int *p_update;
//    p_update = &updates;
//    cout << "这输出的是一个地址 p_update = " << p_update << endl;
//    cout << "这输出的是地址指向的值 *p_update = " << *p_update << endl;
//
//    // 这些都是可以的
//    int *ptr;
//    int *ptr1;
//
//
//    // 这个声明了一个指针，一个普通变量
//    int *ptr3, ptr4;
//
//    double *pDouble = new double;
//    *pDouble = 1111;
//
//    delete pDouble;
//
//    // 创建数组
//    int *psome = new int[3];
//    psome[0] = 1;
//    psome[1] = 2;
//    psome[2] = 3;
//
//    cout << "psome[0] = " << psome[0] << endl;
//    // 相当于psome地址向前移动了，那么本身是0的位置，那么0的位置向前移动了
//    psome += 1;
//    cout << "+1 psome[0] = " << psome[0] << endl;
//    psome -= 1;
//    cout << "-1 psome[0] = " << psome[0] << endl;
//    delete[] psome;
//
//
//    double wages[3] = {10000.0, 20000.0, 30000.0};
//    short tacks[3] = {1, 2, 3};
//
//    double *pWages = wages;// 看来数组本身就是一个地址
//    short *pTacks = &tacks[0];// 如果是地址指向的话，那么应该指向第一个
//    cout << "sizeof(pWages) = " << sizeof(pWages) << endl;
//    cout << "sizeof(tacks[0]) = " << sizeof(tacks[1]) << endl;
//    delete[]pWages;
//    delete[]pTacks;
//
//    struct things {
//        int good;
//        int bad;
//    };
//
//    things *pThings = new things;
//    *pThings = {
//            1, 2
//    };
//    // 这两种访问方式是等价的
//    (*pThings).good;
//    pThings->good;
//    delete pThings;
//
//    static double fee = 56.5;
//
//}