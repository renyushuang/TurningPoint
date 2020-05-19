#include <iostream>

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;

    // 数组声明应指出以下三点
    // 1.存储在每个元素中的值类型
    // 2.数组名
    // 3.数组中的元素数

    short months[3];

    // typeName arrayName[arraySize];
    // arraySize指定元素数量，必须是整型常数，arraySize不能是变量
    // 稍后会有new 运算符来避开这种显示

    // 存值
    months[0] = 1;
    months[1] = 2;
    months[2] = 3;
    // 取值
//    cout << "months 0 = " << months[0] << endl;
//    cout << "months 1 = " << months[1] << endl;
//    cout << "months 2 = " << months[2] << endl;

    int yamcosts[3] = {20, 30, 5};
    int hand[4];
//    hand[4] = {1,2,3,4}; 这是错误的
//    hand = yamcosts;这也是不行的
// 只初始化了前两个元素
    float hotelTips[5] = {5.0, 2.5};


    // c++11的数组初始化
    // 不需要增加 =
    double earnings[4]{1.2e4, 1.6e4, 1.1e4};
    // 将所有元素都设置为 0
    float balances[100]{};
    // 列表初始化禁止缩窄转换
//    long plifs[] = {25, 92,3.0};// double转long是缩窄操作，不能编译通过
//    char slofs[4]{'h', 'i',11211};//11211 超出了char的取值范围，所以编译不过
    char tlifs[4]{'h', 'i', 112};


    char bird[11] = "Mr.Cheeps";
    char fish[] = "Bubbles";
    cout << "11211 超出了char的"
            "取值范围，所以编译不过" << endl;
    const int Size = 15;
    char name1[Size];
    char name2[Size] = "C++owboy";
    name2[3] = '\0';
    cout << name2 << endl;




    // c++11字符串初始化
    char first_data[] = {"aaaaa"};
    char secound_data[]{"aaaaa"};
    string secound_str[]{"aaaaa"};
    string first_srt[]{"aaaaa"};

    // 赋值操作
    string str1;
    string str2 = "panther";
    str1 = str2;
    // 拼接
    string str3;
    str3 = str2 + str1;
    // 附加
    str1 += str2;


    char charr1[] = {"bbb"};
    char charr2[] = {"aaaaa"};
    // 将字符串复制到字符串数组
    strcpy(charr1, charr2);
    cout << charr1 << " strcpy--- " << charr2 << endl;
    // 将字符串附加到数组中
    strcat(charr1, charr2);
    cout << charr1 << " strcat --- " << charr2 << endl;

    // 确定字符串的长度
    str1.size();
    strlen(charr2); // 这个只能用 char[]

    // 这种适用于char[] 输入
    cin.getline(charr1,20);
    // 这种是用于string的输入
    getline(cin,str2);

    return 0;
}
