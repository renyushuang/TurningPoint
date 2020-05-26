#include <iostream>
#include "stock00.h"

void swapr(int &a, int &b);

void swapp(int *p, int *q);

void stapv(int a, int b);

int main() {

    int wallet1 = 300;
    int wallet2 = 350;

    // 这个标识符相当于直接是引用传递
    swapr(wallet1, wallet2);
    swapp(&wallet1, &wallet2);
    stapv(wallet1, wallet2);
    Stock *str = new Stock;
    str->show();
    return 0;
}

void swapr(int &a, int &b) {


}