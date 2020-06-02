# C++语言基础

## 一、预备

C++是在C语言的基础上支持：

- 面向对象
- 范型编程
- 继承了C语言的高效简洁、快速、可移植的传统

面向对象及支持的新术语—对象、类、封装、数据隐藏、多态、继承等

### 1.1 C语言

#### 1.1.1 C语言解决什么问题

汇编语言是低级的语言，直接访问CPU寄存器、内存等，因此平台依赖性极强。在不同的机器上需要使用不同的汇编语言进行编写。

**C语言**可以将低级语言的效率、硬件访问能力、和高级语言的通用性、可移植性融合到一起

#### 1.1.2 C语言编程原理

计算机语言要处理的两个概念—数据和算法

- 数据—是程序使用和处理的信息

- 算法—是程序使用的方法

**所以说数据结构和算法是必须要很好掌握的。**

```
数据 + 算法 = 程序
```

**编程原则**

1.结构化编程—结构化分支限制为以小组行为良好的结构，C语言包含了这些结构：

- for循环
- while循环
- do-while循环
- if else语句

2.自顶向下的设计

- 将大型程序分解成小型、便于管理的任务



#### 1.1.3 面向对象编程

与强调算法的过程性编程不同的是，OOP强调的是数据。**理念**是设计与问题的本质特性相对应的数据格式

- 重用代码
- 信息隐藏可以保护数据，使其避免不正当的访问
- 多态，可以为运算符和函数创建多个定义，通过编程上下文确定哪个定义
- 继承，能够使旧类派生出新类

C++真正的优点之一是：可以方便的重用和修改现有的、经过仔细测试的代码

#### 1.1.4 C++和范型编程

强调独立与特定的数据类型

- 重用代码
- 抽象通用概念



## 二、开始学习C++

### 2.1 第一个程序 “Hello Word”

```c++
// 预处理器 将iostream文件的内容加入到当前程序中
#include <iostream>
// 名称空间支持，根据命名空间来区分版本
using namespace std;

// 注释是以//打头
/* 这是c的注释，C++也可以识别 */

// 在C++程序中，通常由main开始执行
int main() {
    // cout 打印消息
    cout << "come up and C++ me some time.";
    // endl 另起一行 等价于 \n换行符号\n是写在String中的可以减少输入量
    // endl确保程序继续运行前刷新输出，\n不能提供这样的保证，可能会在输入信息后才会出现
    cout << endl;
    cout << "You Won't regret it " << endl;

//    等价于下面这形式
//    std::cout<<"come up and C++ me some time.";
//    std::cout<<std::endl;
//    std::cout<<"You Won't regret it "<<std::endl;
    return 0;
}
```

### 2.2 C++语句

```c++
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
    carrots =25;
    cout<<"I have ";
    cout<<carrots;
    cout<<" carrots";
    cout<<endl;
    // 赋值运算符 右面是一个算数表达式
    carrots = carrots-1;
    cout<<"Crunch crunch ! Now I have "<<carrots<<" Carrots."<<endl;

    return 0;
}
```

结果

```c++
// 对输出内容进行了拼接
I have 1 carrots
Crunch crunch ! Now I have 0 Carrots.
```



### 2.3 c++输入语句

```c++
// 这个是c++输入语句
cin>>carrots;
```

### 2.3.3 类简介

类是用户定义的一种数据类型。

- 需要描述它能够表示什么信息
- 可对数据执行哪些操作

### 2.3.4 函数

#### 2.3.4.1 函数格式

```c++
type functionname(argumentlist){
  statemenrts
}
```

- 自定义函数要在main函数的下边
- c++不准许函数定义到另一个函数的里面，每一个函数的都是独立的

#### 2.3.4.2函数头

```c++
// void 表示没有返回值
void simon(int n)
```

#### 2.3.4.3 由返回值的函数

```c++
int stonetolb(int sts){
		return 14 * sts;
}
```

### 2.5总结

c++程序由一个或多个被称为函数的模块组成的。

多种个类型的c++语句

- 声明语句
- 赋值语句
- 消息语句：将消息发送给对象，激发某种行为
- 函数调用
- 函数原型：声明函数的返回类型、函数接受的参数数量和类型



结下来进入程序的细节



## 三、处理数据

内置的c++类型

- 基本类型
  - 整型和浮点型
- 复合类型(不知道是啥，之后应该会有)
  - 根据基础类型提供的变体
  - 数组
  - 字符串
  - 指针
  - 结构

### 3.1简单变量

程序必须记录3个基本属性：

- 信息将存储在哪里
- 要存储什么值
- 存储何种类型的信息



```c++
// 程序找到一块能够存储整数的内存，将该内存单元标记为braincount，并将5复制到内存单元格中
int branCount;
branCount = 5;
```

#### 3.1.1 变量名

命名规则：

- 在名称中只能使用字母字符、数组、下划线
- 名称的第一个字母不能是数字
- 区分大写小写字符
- 不能将c++关键字用作名称
- 以两个下划线或下划线和大写字母打头的名称被保留给实现（编译器及其使用的资源）使用。以一个下划线开头的名称被保留给实现，用作全局标识符
- c++对于名称的长度没有限制，，名称中多有的字符都是有意义的

倒数第二种 _time_stop 或 _Stop不是语法错误，**不知道将是什么，我也不知道是什么**,说是第四章进行讨论

### 3.1.2 数据类型

#### 3.1.2.1 整型

整型就是整数类型，例如2、98、-5285和0等

- 使用的内存量越大，可以表示的整数值范围也越大。
- 有的类型可以表示正值和负值，而有的类型不能表示负值
- 术语宽度(width)用于描述存储整数时使用的内存量，内存越多，则越宽
- C++基本类型 char short int long longlong，每种都有有符号版本和无符号版本，总共有10种

### 3.1.3 整型short、int、long和longlong

长度:

- short至少16位
- int 至少与short一样长
- long至少32位，且至少和int一样长
- longlong至少64位，且至少与long一样长

c++的内存占用大小和java差别还比较大，java时固定的，c++是根据不同机型有不同的，但原则和上面相同。

```c++
// 这四种都是有符号类型
// 使用和int相同 取值范围
int branCount;
// 实际 short int
short score;
// 实际 long int
long position;
long long ssssss;
std::cout << "score 长度 = " <<sizeof(score)<< std::endl;
std::cout << "int 长度 = " <<sizeof(branCount)<< std::endl;
std::cout << "long 长度 = " <<sizeof(position)<< std::endl;
std::cout << "long long 长度 = " <<sizeof(ssssss)<< std::endl;

```
试了一个我现在的电脑的获取了一下大小，单位 字节 1个字节是8位
```c++
score 长度 = 2
int 长度 = 4
long 长度 = 8
long long 长度 = 8
```

查看当前支持的最大或最小取值

```c++
// int 的最小取值
std::cout << "INT_MIN 长度 = " <<INT_MIN<< std::endl;
// 字节的位数
std::cout << "CHAR_BIT 长度 = " <<CHAR_BIT<< std::endl;
std::cout << "SHRT_MAX 长度 = " <<SHRT_MAX<< std::endl;
std::cout << "LONG_MAX 长度 = " <<LONG_MAX<< std::endl;
std::cout << "LLONG_MAX 长度 = " <<LLONG_MAX<< std::endl;
```

limits.h是存储上面常量的文件，常量声明方式

```c++
#define CHAR_MIN
```

####3.1.3.1 初始化

```c++
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
```

### 3.1.4 无符号类型

例如short 的范围为**-32768—+32767**，无符号的则为0—65535

```c++
// 无符号声明方式
unsigned short int u_hamburgers;
```

### 3.1.6 整型字面值

```c++
// 十进制
int chest = 10;
// 16进制 开头加上0x
int waist = 0x42;
// 8进制 开头增加0
int inseam = 042;
```

这些方法仅仅是为了表示上方便，实际上都被计算机存储为二进制数（以2为基数）

#### 3.1.7 C++如何确定常量类型

```c++
// 默认1492 是存储为int的，除非有特别的理由
std::cout<<"Year = "<< 1492<<std::endl;

22022L // long
22022UL // unsigned long
22022LL // long long   
// 特殊的类型需要再后面增加尾缀
  
```

#### 3.1.8 char 类型：字符和小整数

为存储字符而设计的

美国常用的符号集是ASCLL

IBM使用EBCDIC

c++支持宽字符类型可以支持存储更多的值，例如Unicode

```c++
// 声明字符变量
char ch;
cout << "输入字符" << endl;
cin >> ch;
cout << "输入字符是 = " << ch << endl;
```

结果：

char只能存储一个字符，所以只存储了第一个字符

```c++
输入字符
ss
输入字符是 = s
```

换一种说法：

```c++
    // 声明字符变量
    char ch = 77;
    // 等价于 ch = 'M'
    int chNumber = ch;
    ch = chNumber + 1;
//    cout << "输入字符" << endl;
//    cin >> ch;
    cout.put('c');
    cout<<endl;
    cout << "输入字符是 = " << ch << " --- " << chNumber << endl;
```

##### 2.cout.put是什么

可以代替**<<** 但是只能输入单个字符

为什么会有这个东西

答案与历史有有关。c++Relase2.0之前，cout将字符串变量显示为字符，而将字符常量（如‘M’和‘N’）显示为数字。char占8位，二char的编码存储在16或32位的int中

```c++
// 这个打印的是c的字符
cout.put('c');
// 这个打印的是c的ASCLL码
cout<<'c';
```

##### 4. 通用字符名

\u后是8个16进制

\u00F6rper 

##### 5.signed char 和Unsigned char

取值范围 -127—128    0—255

##### 6.、wchar_t

宽字符

##### 7.c++新增的类型 char16_t和char_32_t

- char16_t无符号长16位
- char_32_t无符号长32位



#### 3.1.9 bool类型

```c++
// bool 默认声明方式
bool is_ready = true;
// bool true 相当于 int ans = 1; 当然也是非0值
int ans = true;
// bool false 相当于 int ans = 0;
int promise = false;

bool start = -100;
// 相当于 false
bool end  = 0;
```

#### 3.2 const限定符号

常量的符号名称。初始化后值就被固定，编译器不准许再修改这个值

```c++
const int Months = 10;
```

#### 3.3 浮点数

#### 3.3.2 浮点类型

float、double、long double

float至少32位

double至少48位而且不少于float

long double至少和double一样多，通常为80、96或128位



cfloat或float.h可以找到系统的限制



#### 3.3.4 浮点数的优缺点

优点：

1.表示整数之间的值

2.由于有缩放因子，可以表示的范围大得多

缺点：

1.运算的速度通常比整数运算慢

2.精度低



#### 3.4 c++算数运算符

```c++
int hats = 10, heads = 5;

cout << "hats + heads = " << hats + heads << endl;
cout << "hats - heads = " << hats - heads << endl;
cout << "hats * heads = " << hats * heads << endl;
cout << "hats / heads = " << hats / heads << endl;
// 取余数
cout << "hats % heads = " << hats % heads << endl;
```

##### 3.4.1 运算符优先级和结合性

##### 3.4.2 除法分支

```c++
9/5; // int除法
9L/5L; // Long除法
9.0/5.0;//double除法
9.0f/5.0f; // float除法
```

##### 3.4.3 求模运算

```c++
const int Lbs_per_stn = 14;
int lbs = 34;

int stone = lbs/Lbs_per_stn;
int pounds = lbs%Lbs_per_stn;
cout<<stone<<" stone "<<pounds<<" pounds"<<endl;
```

##### 3.4.4 类型转换

c++自动执行很多类型转换：

- 将一种蒜素类型的值赋给另一种算数类型的变量时，c++将对值进行转换

- 表达式中包含不同的类型时，c++将对值进行转换
- 将参数传递给函数时，C++将对值进行转换

#### 3.4.5 C++中的auto声明

```c++
auto n = 100;// n为int
auto x = 1.5;// x为double
auto y = 1.3e12L;// y为long double
```



## 四、复合类型

- 介绍复合类型
- 介绍new 和 delete及如何使用他们来管理数据
- 简要的介绍string类

### 4.1 数组

```c++
// 数组声明应指出以下三点
// 1.存储在每个元素中的值类型
// 2.数组名
// 3.数组中的元素数

short months[12];

// typeName arrayName[arraySize];
// arraySize指定元素数量，必须是整型常数，arraySize不能是变量
// 稍后会有new 运算符来避开这种显示
```

```c++
// 存值
months[0] = 1;
months[1] = 2;
months[2] = 3;
// 取值
cout << "months 0 = " << months[0] << endl;
cout << "months 1 = " << months[1] << endl;
cout << "months 2 = " << months[2] << endl;
```

上面的赋值桡了一大圈，使用捷径方式

```c++
int yamcosts[3] = {20, 30, 5};
```

##### 4.1.2 数组的初始化规则

```c++
    int yamcosts[3] = {20, 30, 5};
    int hand[4];
//    hand[4] = {1,2,3,4}; 这是错误的
//    hand = yamcosts;这也是不行的
```

```c++
// 只初始化了前两个元素
    float hotelTips[5] = {5.0,2.5}; 
```

##### 4.1.4 C++11数组初始化方法

```c++
// c++11的数组初始化
// 不需要增加 =
double earnings[4]{1.2e4, 1.6e4, 1.1e4};
// 将所有元素都设置为 0
float balances[100]{};
// 列表初始化禁止缩窄转换
long plifs[] = {25, 92,3.0};// double转long是缩窄操作，不能编译通过
char slofs[4]{'h', 'i',11211};//11211 超出了char的取值范围，所以编译不过 
char tlifs[4]{'h', 'i',112};
```

C++标准模版库增加了一种数组替代品vector

c++11增加了array

这些会在16章进行看

### 4.2 字符串

c-风格字符串

```c++
// c-风格字符串
// 非string
char dog[8] = {'b', 'e', 'a', 'u', 'I', 'I'};
// 以空字符结尾，空字符被写作\0
char cat[8] = {'b', 'e', 'a', 'u', 'I', '\0'};
```

这种方式写起来太恶心了，换一种字符串常量或字符串字面值

```c++
char bird[11] = "Mr.Cheeps";
char fish[] = "Bubbles";
// 这种方式将会自动读到char数组中，并自动加上结尾的空字符
```

#### 4.2.1 拼接字符串常量

```c++
cout<<"11211 超出了char的"
      "取值范围，所以编译不过"
```

#### 4.2.2 在数组中使用字符串

两种方法：

- 数组初始化为字符串常量
- 将键盘或文件输入读入到数组中

不懂如何把string放入数组中

#### 4.2.3 字符串输入

1.面向行的输入 getline()

2.面向行的输入get

3.空行和其他问题 cin.clear进行恢复



### 4.3 string类简介

```c++
string str2 = "panther";
cout << "str2 = " << str2[2] << endl;
```

很多方面，使用string对象的方式与使用字符数组相同：

- 可以使用C-风格字符串来初始化string对象
- 可以使用cin来将键盘输入存储到string对象中
- 可以使用cout来显示string对象
- 可以使用数组表示法老访问存储在string对象中的字符

#### 4.3.1 C++11字符串初始化

```c++
// c++11字符串初始化
char first_data[] = {"aaaaa"};
char secound_data[] {"aaaaa"};
string secound_str[] {"aaaaa"};
string first_srt[] {"aaaaa"};
```

#### 4.3.2 赋值、拼接和附加

```c++
// 赋值操作
string str1;
string str2 = "panther";
str1 = str2;
// 拼接
string str3;
str3 = str2 + str1;
// 附加
str1 += str2;
```

#### 4.3.3 string类的其他操作(这玩意看着只有char数组那么也就是C-风格字符串)

```c++
char charr1[] = {"bbb"};
char charr2[] = {"aaaaa"};
// 将字符串复制到字符串数组
strcpy(charr1, charr2);
cout << charr1 << " strcpy--- " << charr2 << endl;
// 将字符串附加到数组中
strcat(charr1, charr2);
cout << charr1 << " strcat --- " << charr2 << endl;
```

结果：

```c++
aaaaa strcpy--- aaaaa
aaaaaaaaaa strcat --- aaaaa
```

字符串长度：

```c++
// 确定字符串的长度
str1.size();
strlen(charr2); // 这个只能用 char[]
```

#### 4.3.4 string类的I/O

```c++
// 这种适用于char[] 输入
cin.getline(charr1,20);
// 这种是用于string的输入
getline(cin,str2);
```

### 4.4 结构简介

学习有关结构的知识将使我们离c++的核心OOP更近

```c++
struct inflatable{
    char name[20];
    float volume;
    double trice;
};
```

定义好了结构就可以定义变量了：

```c++
inflatable inflatable_a;
inflatable inflatable_b[12];
```

#### 4.4.1 在程序中使用结构

```c++
#include <iostream>

struct inflatable {
    char name[20];
    float volume;
    double trice;
};

using namespace std;

int main() {
		// 初始化方式
    inflatable guest = {
            "renyushuang",
            1.88,
            29.99,
    };
    cout << "guest.name = " << guest.name << endl;
    cout << "guest.volume = " << guest.volume << endl;
    cout << "guest.trice = " << guest.trice << endl;


    return 0;
}
```

- 上面这种属于外部身影，外部声明可以被后面的任何函数使用
- 内部声明只能被该声明所属的函数所用

#### 4.4.2 c++结构初始化

```c++
inflatable mayor = {
};
cout << "mayor.name = " << mayor.name << endl;
cout << "mayor.volume = " << mayor.volume << endl;
cout << "mayor.trice = " << mayor.trice << endl;

// 结果
// mayor.name = 
// mayor.volume = 0
// mayor.trice = 0

```

```c++
inflatable duck{
        "renyushuang",
        1.88,
        29.99,
};
```

#### 4.4.3 结构可以将string类作为成员变量吗？

```c++
using namespace std;

struct inflatable {
    string name;
    float volume;
    double trice;
};
// 看样子没啥问题
```

#### 4.4.4 其他结构属性

```c++
inflatable duck{
        "renyushuang",
        1.88,
        29.99,
};

inflatable choice;
choice = duck;
```

```c++
// 这样的方式也是可以的， 创建两个结构变量
struct inflatable {
    string name;
    float volume;
    double trice;
}mr_smith, ms_ones;
```

```c++
// 声明的同时进行直接赋值
struct inflatable {
    string name;
    float volume;
    double trice;
} mr_smith{
        "name",
        1.1,
        2.2
}, ms_ones;
```

```c++
// 甚至声明的时候可以隐藏名称 no tag
// 这种方式 没有办法创建这种类型的变量，所以分情况使用
struct {
    int x;
    int y;
} position;
```

#### 4.4.5 结构数组

```c++
inflatable gifts[100];
```

数组的初始化：

```c++
struct position {
    int x;
    int y;
};

position gifts[2] = {
        {1, 2},
        {3, 4}
};
// 访问就和正常的数组相同
gifts[0].x
```

#### 4.4.6 结构中的位字段

```c++
// 1.字段的类型应为整型或枚举类型
// 2.冒号后面指定了位数
// 3.每个成员都被称为 字段
struct torgle_register {
    unsigned int SN: 4;
    unsigned int : 4; // 这种没有名称的 提供间距
    bool goodIn: 1;
    bool goodleTorgle: 1;
};
torgle_register x = {4, true, false};
```

### 4.5 共同体（这块不理解，之后用到具体场景再看）

```c++
// 共同体能存储不同的类型，但是只能同时存储一种类型
union une4all {
    int int_val;
    long long_val;
    double double_val;
};
```

它的优势是 使用两种或更多格式时可以节省空间

### 4.6 枚举

可以替代const。实例

```c++
// spectrum 定义枚举名称
enum spectrum {
    red, blue, green, orange//这些是符号常量，对应着整数值0～N，叫做枚举量
};
// 用枚举名称声明这种变量
spectrum band;

// 枚举变量的赋值
band = blue;
//    band = 2000; // 枚举变量只能使用自己定义的值

//    band = 1;// 枚举变量不能自动转为整型
int color = 1 + band; // 但是可以当成整型进行运算

// 可以进行强制类型转换赋值给band类型
band = spectrum(3);
```

#### 4.6.1 设置枚举的值

```c++
enum bits {
    one = 1,
    two = 2,
    four = 4
};
```

```c++
// 也可以只对部分赋值
enum bits {
    one = 1,
    two = 2,
    four
};
```

**难道只能赋值成int**

#### 4.6.2 枚举的取之范围

```c++
enum bits {
    one = 1,
    two = 2,
    four = 10
};
bits my_flag;
// 这个虽然没有具体定义，bits中最小值是1，最大值是10，6是在其中的所以合理
// 试了一下bits(111111112);所以实际长度是由编译器决定的可能是int的最大最小
my_flag = bits(6);
cout << "my_flag = " << my_flag << endl;
```

### 4.7 指针和自由存储空间

计算机程序在存储数据时必须跟踪的3种基本属性：

- 信息存储在何处
- 存储的值为多少
- 存储的信息时什么类型

指针：

- 存储的是值的地址，而不是值本身
- 常规变量的地址 & 例如 &home

```c++
int dounts = 6;
cout << "&dounts = " << &dounts << endl;
```

结果：

```c++
&dounts = 0x7ffee52965fc
```



指针与c++基本原理

- 运行阶段进行决策
- 编译阶段是指编译器将程序组合起来



举一个例子：

1. manly是一个指针
2. 则manly表示的是一个地址
3. *manly表示存储在该地址处的值
4. *manly与常规的int变量等效



```c++
int updates = 10;

int *p_update;
p_update = &updates;
cout << "这输出的是一个地址 p_update = " << p_update << endl;
cout << "这输出的是地址指向的值 *p_update = " << *p_update << endl;
```
结果：
```c++
这输出的是一个地址 p_update = 0x7ffee6f725fc
这输出的是地址指向的值 *p_update = 10
```



#### 4.7.1 声明和初始化指针

```c++
// 这些都是可以的
int *ptr;
int* ptr1;
int*ptr2;
    
// 这个声明了一个指针，一个普通变量
int *ptr3,ptr4;
```

#### 2.7.2 指针的危险

在c++中创建指针时，

1. 计算机将分配用来存储地址的内存，

2. 但不会分配用来存储指针指向的数据内存

#### 4.7.4 使用new来分配内存

看看指针是如何实现程序运行时分配内存的。

指针的用武之地在于，在运行阶段分配未命名的内存以存储

c语言是使用malloc()分配内存

c++

```c++
// new 关键字 找到一个长度正确的内存块
int *pn = new int;
// 这句话做了一个什么样的事情
// new int 创建了一个内存地址空间，并将地址返回
```

作为一个数据对象（可以是结果，也可以是一个基本类型），获得并指定分配内存的通用格式如下：

typeName *Pointer_name = new tyoeName;

```c++
double *pDouble = new double;
*pDouble = 1111;
```

#### 4.7.5 使用delete释放内存

```c++
double *pDouble = new double;
*pDouble = 1111;

// 释放pDouble指向的内存，但不会删除指针pDouble补充
// 一定要记得删除，不然不然会发生内存泄漏
delete pDouble;
```

不要尝试释放已释放的内存

#### 4.7.6 使用new 来创建动态数组

```c++
// 创建数组
int *psome = new int[10];
delete[] psome;
```

使用new和delete时，应遵守以下规则：

- 不要使用delete来释放不是new分配的内存
- 不要使用delete释放同一个内存块两次
- 如果使用new[]为数组分配内存，则应使用delete[]释放内存
- 如果使用new[]为一个实体分配内存则应使用delete来释放
- 对空指针应用delete是安全的

###### 2.使用动态数组

```c++
cout << "psome[0] = " << psome[0] << endl;
// 相当于psome地址向前移动了，相当于psome[0]指向了第二个值
psome += 1;
cout << "+1 psome[0] = " << psome[0] << endl;
psome -= 1;
cout << "-1 psome[0] = " << psome[0] << endl;
delete[] psome;
```

结果：

```c++
psome[0] = 1
+1 psome[0] = 2
-1 psome[0] = 1
```

### 4.8指针、数组和指针算数

指针和数组基本等价的原因在于指针算数和c++内部处理数组的方式。

```c++
double wages[3] = {10000.0, 20000.0, 30000.0};
short tacks[3] = {1, 2, 3};

double *pWages = wages;// 看来数组本身就是一个地址
short *pTacks = &tacks[0];// 如果是地址指向的话，那么应该指向第一个
cout << "sizeof(pWages) = " << sizeof(pWages) << endl;
cout << "sizeof(tacks[0]) = " << sizeof(tacks[1]) << endl;

delete []pWages;
delete []pTacks;
```

### 4.8.3 指针和字符串

#### 4.8.4 使用new创建动态结构

```c++
things *pThings = new things;
*pThings = {
        1, 2
};
// 这两种访问方式是等价的
(*pThings).good;
pThings->good;

delete pThings;
```

#### 4.8.5 自动存储、静态存储和动态存储

c++有3种管理数据内存的方式：

- 自动存储
- 静态存储
- 动态存储

#### 1.自动存储（局部变量）

在函数内定义的常规变量属于自动存储空间

- 调用时自动产生
- 函数结束时消亡

局部变量存储在栈中，执行过程中将依次加入到栈中，而离开时将按相反的顺数释放

#### 2.静态存储

整个程序执行过程中都存在的存储方式

- 在函数外面定义它
- 在声明变量时使用关键字static

```c++
static double fee = 56.5;
```

#### 3.动态存储

new和delete运算符提供一种比自动变量和静态变量更灵活的方法。

管理了一个内存池。c++被称为自由存储空间或者堆

### 4.10 数组的替代品

#### 4.10.1 模版类vector

```c++
#include <iostream>
#include <vector>

using namespace std;

int main() {
		// 不会用
    vector<double> *vDouble = new vector<double>;
    vector<double> vDouble = {1,2,3,4,5};
  	// 这么一看和数组一样
    vDouble[2]= 1;

}
```

#### 4.10.2 模版类array

```c++
#include <array>

using namespace std;

int main() {
    array<double,4> ad= {1,2,3,4};
		ad[3] = 1;
}
```

#### 4.10.3比较数组、vector对象和array对象

使用begin和end避免数组越界



## 五、循环和关系表达式

c++不能放弃，从跳跃的地方重新开始，学习不能着急，稳中求成

### 5.1 for循环

```c++
for (int i = 0; i < 5; i++) {

}
```



#### 5.1.4 使用for循环访问字符串

```c++
string word = "Hello, World!";

for (int i = 0; i < word.size(); i++) {
    cout << "打印 = " << word[i] << endl;
}
```

#### 5.1.1 递增运算符（++）和递减运算符（--）

```C++
int a = 20;
int b = 10;

a++;
b++;
a--;
b--;
++a;
++b;
--a;
--b;
```

#### 5.1.11 其他语法技巧—逗号运算符

```c++
// 类似于这样
for (int j = 0, i = word.size() - 1; j < i; --i, ++j) {

}
```

#### 5.1.14 C-风格字符串的比较

```c++
// == 0 相等 ！=0 不想等 str1在str2前面则<0
strcmp(str1, str2) != 0
```

#### 5.1.15 比较string类字符串

```c++
string word = "Hello, World!";

if (word == "Hello, World!") {
    cout << "相等" << endl;
}
```

### 5.2 while 循环

```c++
char name[] = "11111";
int i = 0;
while (name[i] != '\0') {
    cout << name[i];
    i++;
}
```

#### 5.2.2 等待一段时间：编写延时循环

```c++
// CLOCKS_PER_SEC看当前的时间单位
clock_t i1 = clock() / CLOCKS_PER_SEC;// 可以得到秒数
while (clock() / CLOCKS_PER_SEC - i1 > 1000000 / CLOCKS_PER_SEC);
```

**类的别名**

```c++
// 这个方式不知道是啥
#define BYTE char;
// 这个方式应该是通用的方式
typedef char byte;
```

### 5.3 do while循环

```c++
int j = 0;
do {
    j++;
} while (j < 7);
```

### 5.4 基于范围的for循环(c++11)

```c++
double prices[] = {1, 2, 3, 4, 5};
for (double price:prices) {

}
```

### 5.6 嵌套循环和二维数组

```c++
int maxTemps[4][5] = {
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5}
};

for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
        cout << "maxTemps[" << i << "][" << j << "]" << maxTemps[i][j] << " = " << endl;
    }
}
```



## 六、分支语句和逻辑运算符

```c++
if (1111 == 222) {

}
```

#### 6.1.1 if else 语句

```c++
if(statement){
    
} else{
    
}
```

### 6.2 逻辑表达式

#### 6.2.1 逻辑OR运算符：||

#### 6.2.2 逻辑AND运算符：&&

#### 6.2.4 逻辑NOT运算符：!

### 6.3 字符函数库cctype

### 6.4 ?:运算符

### 6.5 switch 语句

### 6.6 break 和continue语句

#### 6.8.2 写入到文本文件中

```c++
#include <iostream>
#include <fstream>
#include <cctype>

int main() {

    std::ofstream outfile;
    outfile.open("carnf.txt");

    outfile << "name";
    outfile << "renyushuang" ;
    outfile.close();

    return 0;
}
```



## 七、函数—c++的编程模块

### 7.1 复习函数的基本知识

创建自己的函数

- 定义
- 提供原型
- 调用

```c++
#include <iostream>

using namespace std;

void simple();

int main() {

    simple();
    return 0;
}

void simple() {
    cout << "I'm but a simple function. \n";

}
```

#### 7.1.1 定义函数

```c++
void functionName(parameterList){
	statement(s);
	return;
}


typName functionName(parameterList){
	statement(s);
	return value;
}
```

#### 7.1.2 函数原型和函数调用

##### 1.为什么需要原型

是什么：原型描述了函数到编译器的接口

什么用：

```c++
double volume = cube(1);
```

- 告诉编译器这cube()有一个参数，如果没有参数，原型将让编译器能够捕获这种错误
- 其次cube()函数计算完成，将把返回值放置到指定位置-可能是CPU的寄存器，也可能是内存中
- 如果没有这些信息编译器只能进行猜测，而编译器是不会这样做的

##### 2.原型语法

```c++
double cube(double);
```

##### 3.原型功能

- 编译器正常处理函数返回值
- 编译器检查使用的参数数目是否正确
- 编译器检查使用的参数类型是否正确。如果不正确，则转换为正确的类型

### 7.2函数参数和按值传递

c++是 值传递的不是引用传递

```c++
double cube(double);

int main() {

    double side = 10;
    cube(side);
    cout << "resut side = " << side << endl;

    return 0;
}


double cube(double side) {
    side = side + 1;
    cout << "cube side = " << side << endl;
}
```

结果：

```c++
cube side = 11
resut side = 10
```

#### 7.2.1 多个参数

```c++
double cube(double,float);
```

#### 7.2.2 另外一个接受两个参数的函数



### 7.3 函数和数组

```c++
int sum_arr(int arr[], int n) {
    int totle = 0;
    for (int i = 0; i < n; i++) {
        totle = totle + arr[i];
    }

    return totle;
}
```

#### 7.3.1 函数如何使用指针来处理数组

```c++
int sum_arr(int *arr[], int n) {
    int totle = 0;
    for (int i = 0; i < n; i++) {
        totle = totle + (*arr)[i];
    }

    return totle;
}
```

#### 7.3.2 将数组作为参数意味着什么



### 7.10 函数指针

前面越看越迷糊

#### 7.10.1 函数指针的基础知识

- 获取函数的地址
- 声明一个函数指针
- 使用指针来调用函数

##### 1.获取函数的地址

如果think()是一个函数，那么think就是函数的地址

##### 2.声明函数指针

```c++
double cube(double);

int main() {
		// 声明函数指针的方式 pf()是一个返回指针的函数
    // double *pf(int);
		// 正确的声明并可以赋值给它 (*pf)(double)意味着pf是一个指向函数的指针
   	double (*pf)(double);
    pf = cube;
    return 0;
}
```

理解了函数指针，那么下面这个：

```c++
void estimate(int lines, double (*pt)(double));

int main() {

    double (*pf)(double);
    pf = cube;

    estimate(1,pf);

    return 0;
}
```

#### 3.使用指针来调用函数

```c++
double cube(double);

void estimate(int lines, double (*pt)(double));

int main() {

    double (*pf)(double);
    pf = cube;

    // 指针调用
    double x = pf(1);
    cout << "x = " << x << endl;
  	// 这样也是可以的
    // double x = (*pf)(1);
    // cout << "x = " << x << endl;
    return 0;
}

double cube(double side) {
    side = side + 1;
    cout << "cube side = " << side << endl;
    return side;
}
```



#### 7.10.3 深入探讨函数指针



#### 7.10.4 使用typedef进行简化

```c++
typedef double real;
```



## 八、 函数探幽



### 8.1C++内联函数

内联函数是c++为了提高程序运行速度所作出的一项改进



```c++
“编译过程的最终产品是可执行程序——由一组机器语言指令组成。运行程序时，操作系统将这些指令载入到计算机内存中，因此每条指令都有特定的内存地址。计算机随后将逐步执行这些指令。有时（如有循环或分支语句时），将跳过一些指令，向前或向后跳到特定地址。常规函数调用也使程序跳到另一个地址（函数的地址），并在函数结束时返回。下面更详细地介绍这一过程的典型实现。执行到函数调用指令时，程序将在函数调用后立即存储该指令的内存地址，并将函数参数复制到堆栈（为此保留的内存块），跳到标记函数起点的内存单元，执行函数代码（也许还需将返回值放入到寄存器中），然后跳回到地址被保存的指令处（这与阅读文章时停下来看脚注，并在阅读完脚注后返回到以前阅读的地方类似）。来回跳跃并记录跳跃位置意味着以前使用函数时，需要一定的开销”

摘录来自: [美] Stephen Prata. “C++ Primer Plus（第6版）中文版。” Apple Books. 
```



内联函数：c++编译器将使用相应的函数代码替换函数调用。

- 在函数声明前加上关键字inline
- 在函数定义前加上关键字inline

### 8.2 引用变量

#### 8.2.1 创建引用变量

```c++
int rates;
// &不是地址符号，而是类型标识符的一部分
// rodents和rates指向相同的值和内存单元
int &rodents = rates;
```

#### 8.2.2 将引用用作函数参数

```c++
#include <iostream>

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


    return 0;
}
void swapr(int &a, int &b){



}
```

#### 8.2.3引用的属性和特别指出

#### 8.2.4 将引用用于结构

#### 8.2.5 将引用用于类对象

#### 8.2.6 对象、继承和引用

**继承：**使得能够将特性从一个类传递给另一个类的语言特性被称为继承

继承的另一个特性：基类引用可以指向派生类对象，而无需进行强制类型转换

#### 8.2.7 何时使用引用参数

使用引用参数的原因有两个：

- 程序员能够修改调用函数中的数据对象
- 通过传递引用而不是整个数据对象，可以提高程序的运行速度

### 8.3 默认参数

```c++
void setData(int i, int n = 1);
```

### 8.4 函数重载

### 8.5 函数模版<范型>

```c++
// 关键字template和typename是必须的
// 除非将typename更改为class
template<typename AnyType>
void swap(AnyType &a, AnyType &b) {
    AnyType temp;
    temp = a;
    a = b;
    b = temp;
}
```

```c++
int a = 1;
int b = 1;
customSwap(a, b);
```

#### 8.5.1 重载的模版

## 九、内存模版和名称空间

### 9.1 单独编译

















## 十、对象和类

### 10.1 过程性编程和面向对象编程

#### 10.2.2 C++中的类

```c++
class Stock {
// 这个是默认的
private:
    long shares;


public:
    void show();

protected:
    void getName();

};

void Stock::show() {


}

void Stock::getName() {

}
```

##### 1.访问控制

##### 2.控制对象成员的访问：共有还是私有



#### 10.2.3 实现类成员函数

```c++
void Stock::show() {


}

void Stock::getName() {

}
```

##### 1.成员函数说明

##### 2.内联方法

```c++
inline void Stock::getName() {

}
```

##### 3.方法使用哪个对象

#### 10.2.4 使用类

### 10.3 类的构造函数和析构函数

#### 10.3.1 声明和定义构造函数

.h

```c++
#ifndef PART_10_STOCK_H
#define PART_10_STOCK_H


#include <string>

class Stock {
private:
    std::string company;
public:
    Stock(std::string &co);
};


#endif //PART_10_STOCK_H
```

实现：

```c++

#include "stock.h"


Stock::Stock(std::string &co) {
    company = co;
};
```

#### 10.3.2 使用构造函数

```c++
std::string str = "aaaa";
Stock *stock = new Stock(str);
// 下面两种方式是对等的
Stock stock1 = Stock(str);
Stock stock2(str);
```

#### 10.3.3 默认构造函数

没有提供构造函数，默认构造函数如下：

```c++
Stock();
```

```c++
Stock::Stock() {

};
```

#### 10.3.4 析构函数

用构造函数创建对象后，程序负责跟踪该对象，直到其过期为止。对象过期时，程序将自动调用一个特殊的成员函数，该函数的名称令人生畏—析构函数

- 析构函数的名字很特殊
- 另外和构造函数一样没有返回值没有生命类型
- 析构函数没有参数

```c++
Stock::~Stock() {

};
```

调用时机：

- 静态存储，则析构函数将在程序结束时自动被调用
- 自动存储类对象，则构造函数将在程序执行完代码时自动被调用
- 如果是new创建的则会在delete时进行调用

### 10.4 this指针

进行两个对象的比较，选择最大的，不知道返回什么了？？？

```c++
// const 本意是不变的意思 在c++中修饰内置类型变量，自定义对象，成员函数，返回值，函数参数
// const https://www.runoob.com/w3cnote/cpp-const-keyword.html
const Stock &Stock::top_val(const Stock &s) {
    if (s.total_val > total_val) {
        return s;
    }
    return ？？？;
}
```

那么c++的this指针可以解决这个问题

```c++
#include "Stock.h"
// const 本意是不变的意思 在c++中修饰内置类型变量，自定义对象，成员函数，返回值，函数参数
// const https://www.runoob.com/w3cnote/cpp-const-keyword.html
const Stock &Stock::top_val(const Stock &s) {
    if (s.total_val > total_val) {
        return s;
    }
    return *this;
}
```

### 10.5 对象数组

```c++
// 调用默认的构造函数
Stock stocks[4];
// 用构造函数初始化元素
Stock stocks1[4] = {
        Stock(1),
        Stock(2),
        Stock(),
        Stock(4),
};
```

### 10.6 类的作用域

#### 10.6.1 作用域为类的常量

1.使用枚举

```c++
class Bakery {
private:
    enum {
        Months = 12,
    };
};
```

2.使用关键字static

```c++
class Bakery {
private:
    enum {
        Months = 12,
    };
    static const int months = 12;
};
```

### 10.6.2 作用域枚举(c++11)







## 十一、使用类

### 11.1 运算符重载

运算符重载是一种形式的C++多态



运算符重载，例如：

- *运算符用于地址
- c++允许将运算符重载扩展到用户定义的类型（例如+将两对象相加）

将两个数组相加是一种常见的运算，通常使用for循环来实现：

```c++
for(int i =0;i<20;i++){
		evening[i] = sam[i] + janet[i];
}
```

可以定义一个表示数组的类，并重载+运算符，于是可以有这样的语句：

```c++
evening = sam + janet;
// 隐藏了内部机理，强掉了实质，这是OOP的另一个目标
```


### 11.2 计算时间：一个运算符重载示例

```c++
//
// Created by 任玉双 on 2020/5/26.
//

#ifndef PART_11_TIME_H
#define PART_11_TIME_H


class Time {
private:
    int hours;
    int minutes;

public:
    Time();

    Time(int h, int m = 0);

    Time Sum(const Time &time);
};


#endif //PART_11_TIME_H
```

#### 10.2.1 添加加法运算符

```c++
class Time {
private:
    int hours;
    int minutes;

public:
    Time();

    Time(int h, int m = 0);

    Time Sum(const Time &time);

    Time operator+(const Time &time);
};
```

看我增加了个啥

```c++
Time Time::operator+(const Time &time) {
    Time sum;
    sum.minutes = this->minutes + time.minutes;
    sum.hours = this->hours + time.hours + sum.minutes / 60;
    sum.minutes % 60;
    return sum;
}
```

#### 11.2.2 重载限制

- 重载后至少有一个操作数是用户定义的类型
- 使用运算符时不能违反运算符原来的句法规则
- 不能创建新的运算符
- 不能重载下面的运算符（sizeof、.:、.*、？::）
- 

### 11.3 友元

c++控制对类对象的私有部分的访问。通常公有类方法提佛那个唯一的访问途径，这种限制太严格以至于不适合特定的编程问题。在这种情况下，c++提供另外一种形式的访问权限：友元

- 友元函数
- 友元类
- 友元成员函数

之前的创建

A=B*2.75这个时可以的



A= 2.75*B这个时不行的，原因在于重载的函数时B的



可以定义一下非成员函数

Time operator*(double m,const time &t)

非成员函数不能访问类的私有数据，有一类特殊的非成员函数可以访问类的私有成员，他们称为友元函数



#### 11.3.1 创建友元

```c++
//“虽然operator *( )函数是在类声明中声明的，但它不是成员函数，因此不能使用成员运算符来调用；
//虽然operator *( )函数不是成员函数，但它与成员函数的访问权限相同。”
friend Time operator*(double m, const Time &time);
```

友元函数是非成员函数，访问权限和成员函数相同



```c++
// 从这来看成员函数还是非成员
Time operator*(double m, const Time &time) {
    return Time();
}
// 成员函数要有所属的类名 Time::
Time::Time() {

}
// 具体试一下就知道 上面说的问题了
Time Time::operator+(const Time &time) {
    Time sum;
    sum.minutes = this->minutes + time.minutes;
    sum.hours = this->hours + time.hours + sum.minutes / 60;
    sum.minutes % 60;
    return sum;
}
```


#### 11.3.2 常用的友元：重载<<运算符

##### 1.<<的第一种重载版本

```c++
friend void operator<<(std::ostream &os, const Time &time);
```



```c++
void operator<<(std::ostream &os, const Time &time) {
    os<<time.hours<<" hours "<<time.minutes<<" minutes ";
}
```



##### 2.<<第二种重载方式

```c++
std::ostream &operator<<(std::ostream &os, const Time &time) {
    os << time.hours << " hours " << time.minutes << " minutes ";
}
```

#### 11.6.1 转换函数

```c++
// 定义
operator double();
```

```c++
// 实现
Time::operator double() {
    return 0;
}
```





