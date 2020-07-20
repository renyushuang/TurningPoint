//
// Created by 任玉双 on 2020/7/20.
//
#include "a_wertyu.h"

//“输入一个错位后敲出的字符串，输出打字员本来想打出的句子。
//样例输入：O S, GOMR YPFSU/
//样例输出：I AM FINE TODAY.”

char *s = "'1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";

void wertyuMain() {
    std::cout << "wertyuMain" << std::endl;

    int i, c;
    while ((c = getchar()) != EOF) {
        for (i = 1; s[i] && s[i] != c; i++);
        if (s[i]) {
            putchar(s[i - 1]);
        } else {
            putchar(c);
        }
    }
}