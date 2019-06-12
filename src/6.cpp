// 第六章：类的其他特性
#include <iostream>
#include <cstring>
using namespace std;

class virBase {
public:
    // 定义了纯虚函数的类为抽象类，不能实例化
    virtual void yell() = 0;
};

class Base:public virBase {
private:
    int p;
public:
    int n;
    Base(int show):p(show), n(show){
        cout << "Base calling consruct function " << show << endl;
    }
    Base(){
        p = 0;
    }
/*
 * 友元函数
 * == 普通函数
 * > 能够访问类中的私有成员和保护成员
 * 1. 在类体内说明，但是并不是类的成员函数
 * 2. 破坏了类的封装性
 * 3. 不带this指针，因此必须有对象名或指针参数
 * 4. 不受private public protected关键字限制，放在类的任意部分都一样
 * 5. 
 */    
    friend void show(const Base &b);
    /* 
     * 虚函数
     * 在基类将同名函数声明为虚函数，则在使用**基类指针或引用**获得派生类值时，可以根据不同派生类，调用不同同名函数
     * 在派生类中重新定义时，可以不加virtual修饰符
     * !可以吧析构函数定义为虚函数
     */
    virtual void yell() {
        cout << "I am Base!\n";
    }
};


class XBase {
private:
    int p;
protected:
    int n;
    XBase(int show):p(show), n(show+1){
        cout << "XBase calling construct function " << show << endl;
    }
    XBase(){
        p = 0;
    }
    friend void show(const XBase &xb);
};

class RC: public Base {
private:
    int x;
protected:
    int y;
public: 
    int z;
    RC();
    RC(int m1, int m2, int m3);
    RC(int show);
    RC(const RC& a);
    void yell() {
        cout << "I am RC!\n";
    }
    friend ostream &operator<<(ostream&, RC&);
}; 

class SC: public RC{
public:
    SC();
    SC(int show);
    void yell() {
        cout << "I am SC!\n";
    }
};

class CC: public SC {
public:
    CC();
    CC(int show);
    void yell() {
        cout << "I am CC!\n";
    }
};

class XC: public CC, public XBase{
public:
    XC();
    XC(int show);
    void yell() {
        cout << "I am XC!\n";
    }
};

class TC: public virtual Base {
public:
    int t;
    TC();
    TC(int show);
    // 友元类，类HC为类TC的友元类
    // HC能访问TC的所有成员
    // 但是HC无法访问TC基类的private成员，因为TC自己也不能访问
    friend class HC;
}; 

class HC: public virtual Base {
public:
    int h;
    HC();
    HC(int show);
    void foo(TC &tc);
};

class HTC: public HC, public TC {
private:
    // 常数据成员
    // 只能通过初始化列表来初始化，任何函数都不能改变它的值
    const int constht;
public:
    // 静态成员
    // 该类产生的所有对象共享一个静态成员
    // 1. 编译时就对静态成员进行空间分配
    // 2. 必须在文件作用域中对静态成员做一个定义性说明
    // 3. 定义性说明时，可以指定一个初值，否则默认为0
    // 4. 可以通过域操作符直接调用，HTC::htc
    static int htc;
    int ht;
    HTC();
    HTC(int show);
    // 全场唯一正常函数：
    void normal() {
        cout << "I am normal.\n";
    }

    /* 
     * 静态成员函数
     * 1. 也可以用域操作符调用
     * 2. 静态成员函数只能使用本类的静态成员
     * 3. 不能直接使用非静态数据成员，可以通过引用使用
     */
    static void htcShow(HTC &c) {
        cout << htc << '\t' << c.ht << endl;
    }
    
    // 常成员函数
    // 不能调用非常成员函数
    // const可以作为重载函数的区分
    void constHTC() const{
        cout << "yes" << endl;
    }

    // 非常成员函数：常对象无法调用
    void constHTC() {
        ht++;
        cout << "no" << endl;
    }
};
// 说明静态成员
int HTC::htc = 5;

int main() {
    HC hc1(1);
    TC tc1(2);
    hc1.foo(tc1);

    Base *pb;
    Base b(1);
    RC rc1(1);
    SC sc1(1);
    CC cc1(1);
    XC xc1(1);

    pb = &b;
    pb->yell();
    pb = &rc1;
    pb->yell();
    pb = &sc1;
    pb->yell();
    pb = &cc1;
    pb->yell();
    pb = &xc1;
    pb->yell();
    /*
    I am Base!
    I am RC!
    I am SC!
    I am CC!
    I am XC!
     */

    HTC htc1(1), htc2(2);
    //htc1.htc = 999;
    //cout << htc2.htc << endl;

    // 直接使用类名加域操作符来调用：
    HTC::htcShow(htc1);

    // 常对象
    // 定义时必须初始化，且在生命周期内不能更新
    // 常对象只能调用const函数(不改变普通成员值的成员函数)
    const HTC htc3(3);
    HTC const htc4(4);
    HTC htc5(5);
    htc3.constHTC();
    htc4.constHTC();
    htc5.constHTC();
    /* 指向类成员的指针
     * 1. 不是类的成员
     * 2. 可指向类的数据成员（不是对象的数据成员）
     * 3. 使用指针时，必须用已经实例化的对象来使用
     * 4. 这种指针只能访问公有成员
     */ 
    int HTC::*ptrHtc;
    ptrHtc = &HTC::ht;
    cout << htc5.*ptrHtc << endl; // 这里htc5.ht已经在210行中自增了1

    /* 指向成员函数的指针变量
     * 1. 不是类的成员
     * 2. 只有 1 参数个数 2 参数类型 3 参数顺序 4 函数类型 和这个变量均一样时，才能将成员函数赋值给指针
     * 3. 必须用对象引用
     * 4. 只能调用公有成员函数
     */
    void (HTC::*ptrNor)();
    ptrNor = HTC::normal;
    (htc5.*ptrNor)();
    return 0;
}

// 友元类
void HC::foo(TC &tc) {
    cout << tc.t << '\t' << tc.n << endl;
}

// 友元函数show
void show(const Base &b) {
    cout << b.n << '\t' << b.p << endl;
}

void show(const XBase &xb) {
    cout << xb.n << '\t' << xb.p << endl;
}

// HTC
HTC::HTC():HC(), TC(), constht(0), ht(h+t) {
    ;
}

HTC::HTC(int show):HC(show), TC(show), constht(show), ht(h-t) {
    cout << "HTC calling construct function " << show << endl;
}

// HC
HC::HC():Base(), h(0) {
    ;
}

HC::HC(int show):Base(show), h(show) {
    cout << "HC calling construct function " << show << endl;
}

// TC
TC::TC():Base(), t(0) {
    ;
}

TC::TC(int show):Base(show), t(show) {
    cout << "TC calling construct function " << show << endl;
}

// XC
XC::XC():CC(), XBase() {
    ;
}

XC::XC(int show):CC(show), XBase(show) {
    cout << "XC calling construct function " << show << endl;
}

// CC
CC::CC():SC() {
    ;
}

CC::CC(int show):SC(show) {
    cout << "CC calling construct function " << show << endl;
}

// SC
SC::SC():RC(0, 0, 0) {
    ;
}

SC::SC(int show):RC(show) {
    cout << "SC calling construct function " << show << endl;
    this->y = 1;
    this->z = 1;
}

// RC
RC::RC(int m1, int m2, int m3):x(m1), y(m2), z(m3){
    ;
};

RC::RC() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
    cout << "Default construct function.\n";
}

RC::RC(int show):Base(show) {
    cout << "RC calling construct function " << show << endl;
    this->x = 0;
    this->y = 0;
    this->z = 0;
};

RC::RC(const RC& a) {
    cout << "RC calling copy construct function.\n";
    this->x = a.x;
    this->y = a.y;
    this->z = a.z;
}

// output
ostream& operator<<(ostream& os, RC& a) {
    os << ' '  << a.x << ' '  << a.y << ' '  << a.z;
    cout << endl;
    return os; 
}
