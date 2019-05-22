#ifndef MYSTRING_H
#define MYSTRING_H
#include "iostream"
using namespace std;
//TODO: 比较运算符重载
// 增加toInt,toFloat，其中Int，float也是自己制作的就好了
// n个赋值运算
// 如果能自动赋值就好了
// 字符串的find函数
// 理论上无限长，但是计数已经限制在int类型中了，除非你自己实现了无限长的int
// index是记录位置肯定没错，count是计数肯定没错，find表示查找子句？
class MyString{
    char* s;
    public:
    // 初始化函数
    MyString();
    MyString(int i);
    MyString(double f);
    MyString(char c);
    MyString(char const *s); 
    MyString(MyString const &ms);
    // 拼接函数
    friend MyString operator+(char c, MyString const &ms);
    friend MyString operator+(MyString const &ms, char c);
    friend MyString operator+(MyString const &ms, char const *s);
    friend MyString operator+(char const *s, MyString const &ms);
    friend MyString operator+(MyString const &ms1, MyString const &ms2);
    // 拼接函数2
    void operator+=(char c);
    void operator+=(char const *s);
    void operator+=(MyString const &ms);
    MyString& operator--();
    MyString operator--(int);
    // 复制函数
    MyString& operator=(char c);
    MyString& operator=(char const *s);
    MyString& operator=(MyString const &ms);
    // 提取字符函数，支持负数，end
    char operator[](int index);
    MyString operator()(int index); 
    MyString operator()(int ind_start, int index_end); 
    // 判断函数
    bool operator==(char c); 
    bool operator!=(char c);
    bool operator==(char const *s);
    bool operator!=(char const *s);
    bool operator==(MyString const &ms);
    bool operator!=(MyString const &ms);
    // 获取长度，常成员函数, 它不改变对象的成员变量.也不能调用类中任何非const成员函数。
    int length() const; 
    // 打印函数
    void inline print(){cout << this->s <<endl;}
    void inline print(char const *str){cout << str << this->s <<endl;}
    friend ostream& operator<<(ostream &out, MyString &ms);
    friend istream& operator>>(istream &in, MyString &ms);
    // 析构函数
    ~MyString();
};

#endif