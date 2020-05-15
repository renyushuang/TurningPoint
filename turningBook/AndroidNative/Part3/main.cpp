#include <iostream>

int main() {



    int branCount;
    short score;
    long position;
    long long ssssss;
    std::cout << "score 长度 = " <<sizeof(score)<< std::endl;
    std::cout << "int 长度 = " <<sizeof(branCount)<< std::endl;
    std::cout << "long 长度 = " <<sizeof(position)<< std::endl;
    std::cout << "long long 长度 = " <<sizeof(ssssss)<< std::endl;

    // int 的最小取值
    std::cout << "INT_MIN 长度 = " <<INT_MIN<< std::endl;
    // 字节的位数
    std::cout << "CHAR_BIT 长度 = " <<CHAR_BIT<< std::endl;
    std::cout << "SHRT_MAX 长度 = " <<SHRT_MAX<< std::endl;
    std::cout << "LONG_MAX 长度 = " <<LONG_MAX<< std::endl;
    std::cout << "LLONG_MAX 长度 = " <<LLONG_MAX<< std::endl;


    // 基础的初始化
    int uncles = 5;
    int aunts = uncles;
    int chairs  = uncles+aunts+1;
    // c++11 的一些初始化
    // 这种方式用作数组和结构,c++98中用作单个变量
//    int hamburgers = {24,12}; //这个是报错的
    int hamburgers = {24};
    std::cout << "hamburgers 值 = " <<hamburgers<< std::endl; //hamburgers 值 = 24
    // c++11 不用 = 号也可以声明
    int emus{7};
    std::cout << "emus 值 = " <<emus<< std::endl;// emus 值 = 7 书上写错了，写了个5
    int rheas = {12};
    // {}中可以没有东西初始化位 0
    int rocs = {12};

    // 无符号声明方式
    unsigned short int u_hamburgers;


    // 十进制
    int chest = 10;
    // 16进制 开头加上0x
    int waist = 0x42;
    // 8进制 开头增加0
    int inseam = 042;

    // 默认1492 是存储为int的，除非有特别的理由
    std::cout<<"Year = "<< 1492<<std::endl;

    

    return 0;
}
