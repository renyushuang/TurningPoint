//
// Created by 任玉双 on 2020/5/26.
//

#ifndef PART_10_STOCK_H
#define PART_10_STOCK_H


#include <string>

class Stock {
private:
    std::string company;
public:
    Stock(std::string &co);
    Stock();
    ~Stock();
};


#endif //PART_10_STOCK_H
