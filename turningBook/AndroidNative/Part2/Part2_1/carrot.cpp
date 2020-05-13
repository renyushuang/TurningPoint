//
// Created by 任玉双 on 2020/5/7.
// C++语句
//
#include <iostream>
using namespace std;

int main() {
    // 声明 1.需要的内存和 2.该内存的单元名称
    int carrots;
    // 赋值语句 将值赋值给存储单元 = 是赋值运算符
    // 这个是c++输入语句
    cin>>carrots;
    cout<<"I have ";
    cout<<carrots;
    cout<<" carrots";
    cout<<endl;
    // 赋值运算符 右面是一个算数表达式
    carrots = carrots-1;
    cout<<"Crunch crunch ! Now I have "<<carrots<<" Carrots."<<endl;

    return 0;
}
