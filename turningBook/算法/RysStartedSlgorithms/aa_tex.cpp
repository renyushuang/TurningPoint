//
// Created by 任玉双 on 2020/7/21.
//

#include "aa_tex.h"
#include <iostream>
//“在TeX中，左双引号是``，右双引号是''。输入一篇包含双引号的文章，你的任务是把它转换成TeX的格式。
//样例输入：
//"To be or not to be," quoth the Bard, "that
//is the question".
//样例输出：
//``To be or not to be,'' quoth the Bard, ``that
//        is the question''.”


void texMain() {
    int c, q = 1;
    while ((c = getchar()) != EOF) {

        if (c == '"') {
            printf("%s", q ? "``" : "''");
            q = !q;
        } else {
            printf("%c", c);
        }
    }
}