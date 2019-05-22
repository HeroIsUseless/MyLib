// 万能变量类，可以表示任何基础基础，让C++变成一个弱类型语言
// 可以由任何int, float, char, string, 用的时候，根据类型自动返回最佳数据类型，也可以进行强制类型转换
// 如何进行转换，参照JavaScript
// 先完善My库先
// 至于更短的，需要工业级强度才行
// 理论上能存无限长的数字和字符串
// 但是，作为这个语言来说，它根本就不能表示那么长的数字。。。这也是唯一的缺憾，因此我提供了var.toInt(char* cs)的函数
// 如果太长，就会返回最大值，向上满溢，就是这样
// 要求：C++11及以上
// 理论上无限长的int类型，转换为普通int类型溢出只能返回满值
// 理论上无限长的float类型
// string类型
// 可以是普通数组，可以是单元数组
// 因为可以输入任意值，因此它的元素必须也是MyValue类型的
// 因为可以输入任意数组，因此它的元素必须
// 先不允许嵌套数组
// 先用初始类型定义，如果是已经造出来的可以使用
// 可以是map
#include "iostream"
#include "vector"
#include "MyString.h"
using namespace std;
enum VarType{Null, Int, Float, Char, String, Vector};
class MyValue{
    int i;
    float f;
    char c;
    MyString str;
    vector<MyValue> v;
    VarType vt;
    public:
    MyValue(); 
    MyValue(int i);
    MyValue(float f);
    MyValue(char c);
    MyValue(char *s);
    MyValue(initializer_list<MyValue> il);
    int toInt();
    int toInt(char *s);
    float toFloat();
    float toFloat(char *s);
    char* toString();
    void print();
    ~MyValue();
};

// MyValue::MyValue();
MyValue::MyValue(int i){
    this->i = i;
    vt = Int;
}
MyValue::MyValue(float f){
    this->f = f;
    vt = Float;
}
MyValue::MyValue(initializer_list<MyValue> il){
    for(auto mv:il)
		v.push_back(mv);	
    vt = Vector;
}
// MyValue::MyValue(char cc);
// MyValue::MyValue(char *cs);
void MyValue::print(){
    if(this->vt == Int) cout << this->i <<endl;
    else if(this->vt == Float) cout << this->f <<endl;
    else if(this->vt == Vector){
        for(auto mv : this->v){
            mv.print();
        }
    }
}
int main(){
    MyValue mv({1, 2, 3});

    return 0;
}