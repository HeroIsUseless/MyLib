#include "iostream"
#include "MyString.h"
#include "string"
using namespace std;

MyString::MyString(){
    this->s = new char[1];
    this->s[0] = '\0';
}

MyString::MyString(int i){
    char s_tmp[20] = {0}; 
    int n=0;
    while(i!=0){
        s_tmp[n++] = i%10 + 48;
        i /= 10;
    }
    this->s = new char[n+1];
    for(int i=0; i<n; i++){this->s[i] = s_tmp[n-1-i];}
    this->s[n] = '\0';
}

MyString::MyString(double f){
    char s_fron[20] = {0};
    char s_back[20] = {0};
    int n_fron=0, n_back=0;
    int f_fron = f; // 整数部分
    float f_back = f - f_fron; // 小数部分
    // 计算整数部分
    while(f_fron!=0){
        s_fron[n_fron++] = f_fron % 10;
        f_fron /= 10;
    }
    // 计算小数部分
    double t = f_back, pow=0.1;
    while(f_back > 0.00001)
	{
        f_back -= pow*(int)(t*10);
        pow *= 0.1;
        s_back[n_back++] = (int)(t*10);	
        t = t*10 - (int)(t*10);
	}  
    // 合并
    this->s = new char[n_fron + n_back + 1];
    for(int i=0; i<n_fron; i++){ this->s[i] = s_fron[n_fron-1-i] + 48; }
    this->s[n_fron] = '.';
    for(int i=0; i<n_back; i++){ this->s[n_fron+1+i] = s_back[i]+48; }
    this->s[n_fron+n_back+1]='\0';
}

MyString::MyString(char c){
    this->s = new char[2];
    this->s[0] = c;
    this->s[1] = '\0';
}

MyString::MyString(char const *s){
    int n=0; while(s[n] != '\0') n++;
    this->s = new char[n+1];
    for(int i=0; i<n; i++) this->s[i] = s[i];
    this->s[n] = '\0';
}

MyString::MyString(MyString const &ms){
    int n = ms.length()+1;
    this->s = new char[n];
    for(int i=0; i<n; i++) s[i] = ms.s[i];
}
MyString operator+(char c, MyString const &ms){
    MyString ms_tmp(c);
    ms_tmp += ms;
    return ms_tmp;
}

MyString operator+(MyString const &ms, char c){
    MyString ms_tmp(ms);
    ms_tmp += c;
    return ms_tmp;
}

MyString operator+(char const *s, MyString const &ms){
    MyString ms_tmp(s);
    ms_tmp += ms;
    return ms_tmp;
}

MyString operator+(MyString const &ms, char const *s){  
    MyString ms_tmp(ms);
    ms_tmp += s;
    return ms_tmp;
}

MyString operator+(MyString const &ms1, MyString const &ms2){
    MyString ms_tmp(ms1);
    ms_tmp += ms2;
    return ms_tmp;
}

MyString& MyString::operator=(char c){
    delete[] this->s;
    this->s = new char[2];
    this->s[0] = c;
    this->s[1] = '\0';
    return *this;
}
MyString& MyString::operator=(char const *s){
    int n=0; while(s[n]!=0) n++;
    delete[] this->s;
    this->s = new char[n+1];
    for(int i=0; i<n+1; i++) this->s[i] = s[i];
    return *this;
}

MyString& MyString::operator=(MyString const &ms){
    int n = ms.length();
    delete[] this->s; this->s = new char[n+1];
    for(int i=0; i<n+1; i++) this->s[i] = ms.s[i];
    return *this;
}

void MyString::operator+=(char c){
    int n = this->length();
    char *s_tmp = new char[n+2];
    for(int i=0; i<n; i++) s_tmp[i] = this->s[i];
    s_tmp[n] = c;
    s_tmp[n+1] = '\0';
    delete[] this->s; this->s = new char[n+2];
    for(int i=0; i<n+2; i++) this->s[i] = s_tmp[i]; 
    delete[] s_tmp;
}

void MyString::operator+=(char const *s){
    int n1 = this->length(), n2 = 0;
    while(s[n2]!=0) n2++;
    char *s_tmp = new char[n1+n2+1];
    for(int i=0; i<n1; i++) s_tmp[i] = this->s[i];
    for(int i=0; i<n2; i++)  s_tmp[n1+i] = s[i];
    s_tmp[n1+n2] = '\0';
    delete[] this->s; this->s = new char[n1+n2+1];
    for(int i=0; i<n1+n2+1; i++) this->s[i] = s_tmp[i]; 
    delete[] s_tmp;
}


void MyString::operator+=(MyString const &ms){
    int n1 = this->length(), n2 = ms.length();
    char *s_tmp = new char[n1+n2+1];
    for(int i=0; i<n1; i++) s_tmp[i] = this->s[i];
    for(int i=0; i<n2+1; i++)  s_tmp[n1+i] = ms.s[i];
    delete[] this->s; this->s = new char[n1+n2+1];
    for(int i=0; i<n1+n2+1; i++) this->s[i] = s_tmp[i]; 
    delete[] s_tmp;
}
// 前置，--(--c)，它考虑的是这个
MyString& MyString::operator--(){
    int i, n = this->length();
    if(n == 0) return *this;
    char *s = new char[--n];
    for(i=0; i<n; i++) s[i] = this->s[i+1]; 
    s[i] = '\0';    
    delete[] this->s;
    this->s = s;
    return *this;
}
// 后置，因为返回的是一个临时对象，但是它有一点，它不能连减了。。
MyString MyString::operator--(int){
    MyString ms_tmp(*this);
    int i, n = this->length();
    if(n == 0) return *this;
    char *s = new char[--n];
    for(i=0; i<n; i++) s[i] = this->s[i];   
    s[i] = '\0';  
    delete[] this->s;
    this->s = s;
    return ms_tmp;
}

char MyString::operator[](int index){
    int len = this->length;
    if(index > 0) return this->s[index];
    else return this->s[len+index];
}

MyString MyString::operator()(int index){
    MyString ms;
    int len = this->length;
    if(index > 0) ms = this->s[index];
    else ms = this->s[len+index];      
    return ms;
}

MyString MyString::operator()(int ind_start, int index_end){ // TODO:不支持负数，end
    MyString ms;
    for(int i=ind_start; i<index_end; i++){
        ms += this[i];
    }
    return ms;
}

int MyString::length() const {
    int n=0;
    while(this->s[n] != '\0') n++;
    return n;
}

bool MyString::operator==(char c){
    if(this->length()==1 && this->s[0]==c) return true;
    else return false;
}

bool MyString::operator!=(char c){
    if(this->length()==1 && this->s[0]==c) return false;
    else return true;
}

bool MyString::operator==(char const *s){
    int n=0; while(s[n] != '\0') n++; //TODO:没有进行try catch设置
    if(n != this->length()) return false;
    else{
        for(int i=0; i<n; i++){
            if(this->s[i] != s[i]) return false;
        }
    }
    return true;
}

bool MyString::operator!=(char const *s){
    int n=0; while(s[n] != '\0') n++; //TODO:没有进行try catch设置
    if(n != this->length()) return true;
    else{
        for(int i=0; i<n; i++){
            if(this->s[i] != s[i]) return true;
        }
    }
    return false;
}

bool MyString::operator==(MyString const &ms){
    if(this->length() != ms.length()) return false;
    for(int i=0; i<this->length(); i++){
        if(this->s[i] != ms.s[i]) return false;
    }
    return true;
}

bool MyString::operator!=(MyString const &ms){
    if(this->length() != ms.length()) return true;
    for(int i=0; i<this->length(); i++){
        if(this->s[i] != ms.s[i]) return true;
    }
    return false;
}

ostream& operator<<(ostream &out, MyString &ms){
    out << ms.s;
    return out;
}

istream& operator>>(istream &in, MyString &ms){
    char *c_tmp = new char[10000];
    in >> c_tmp;
    int i, n;
    for(int n=0; n<10000; n++){
        if(c_tmp[n] == '\0') break;
    }
    char *c = new char[n+1];
    for(i=0; i<n; i++){
        c[i] = c_tmp[i];
    }
    c[i] = '\0';
    delete[] c_tmp;
    delete[] ms.s;
    ms.s = c;
    return in;
}

MyString::~MyString(){
    delete[] this->s;
}

int main(){
    cout << "\nMyString class test:\n" <<endl;
    MyString ms1; ms1.print("Default constructor");
    MyString ms2(12345); ms2.print("int_to_str constructor:");
    MyString ms3(1.2345); ms3.print("float_to_str constructor:");
    MyString ms3_1('a'); ms3_1.print("char_to_str constructor:");
    MyString ms4("abcde"); ms4.print("char*_to_str constructor:");
    MyString ms5(ms4); ms5.print("copy constructor:");
    MyString ms6('z'+ms5); ms6.print("char+str overload:");
    MyString ms7(ms5+'z'); ms7.print("str+char overload:");
    MyString ms7_1(ms7+"aaaaaaaa"); ms7_1.print("str+char* overload:");
    MyString ms7_2("aaaaaaaa"+ms7); ms7_2.print("char*+str overload:");
    MyString ms8(ms5+ms6); ms8.print("str+str overload:");
    char c = 'a'; ms8 = c; ms8.print("=char overload:");
    ms8 = "ms7"; ms8.print("=char* overload:");
    ms8 = ms7; ms8.print("=str overload:");
    ms8 += c; ms8.print("+=char overload:");
    ms8 += "aaaaa"; ms8.print("+=char* overload:");
    ms8 += ms7; ms8.print("+=str overload:");
    cout << ms8[1]<<endl;
    if(ms8 == ms8) cout << "ok1" <<endl;
    if(ms8 != ms7) cout << "ok2" <<endl;
    //cout << "cout:"<<ms8<<endl<<"please:";
    //cin >> ms8;
    //cout << "cout2:"<<ms8<<endl;
    MyString ms9('c');
    if(ms9 == 'c') cout << "ms9:ok" <<endl;
    if(ms9 != 'b') cout << "ms9:no" <<endl;
    MyString ms10("abcdefghi");
    if(ms10 == "abc") cout << "ms10:ok" <<endl;
    if(ms10 != "abd") cout << "ms10:no" <<endl;
    --(--ms10); ms10.print();
    ms10--;
    ms10.print();
    return 0;
}
