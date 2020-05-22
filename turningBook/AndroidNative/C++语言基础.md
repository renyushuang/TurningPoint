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



