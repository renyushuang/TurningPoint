#include <iostream>
#include "stock.h"

int main() {
    std::cout << "Hello, World!" << std::endl;


    std::string str = "aaaa";
    Stock *stock = new Stock(str);
    // 下面两种方式是对等的
    Stock stock1 = Stock(str);
    Stock stock2(str);

    return 0;
}
