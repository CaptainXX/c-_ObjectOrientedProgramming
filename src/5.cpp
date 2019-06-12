// 第五章：继承和派生类
#include <iostream>
#include <cstring>
using namespace std;
// 20190612下午 进度：ppt P22

// 抽象类：构造函数或析构函数访问权限定义为protected
// 抽象类只能作为基类来派生新类
// 构造函数或析构函数为private的类是没有意义的
class Base {
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
};

// 抽象类
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
    friend ostream &operator<<(ostream&, RC&);
}; 

/* 三种派生方式：public protected private
 * 派生类均不可访问基类的private成员 
 * 默认派生方式为private
 * private: 基类所有成员保持原有访问权限
 * protected: 基类public成员变为派生类的protected，外部不可访问，派生类的派生类还能访问
 * private: 基类public protected成员，都变为派生类的private，派生类可以访问，但派生类的派生类就不能访问了
*/
class SC: public RC{
public:
    SC();
    SC(int show);
    // public 继承，SC能访问 y z，不能访问x
    void testPublic();
};

class CC: public SC {
public:
    CC();
    CC(int show);
    void testPrivate();     // 当SC为private派生时，此函数报错
};

// 多重继承，由多个基类派生出一个类
// 继承时CC在前，所以调用构造函数时，CC先调用，XBase后调用
class XC: public CC, public XBase{
public:
    XC();
    XC(int show);
    // 不同基类有相同名称的数据成员时，调用会产生冲突，这时使用域运算符解决
    // 若不加限制，则优先调用派生类的成员，如派生类没有同名成员，则会出错
    void sameName();
};

// 虚基类：编译多态性
// 虚基类在多个派生类的派生类中只有一份拷贝

/* 用虚基类进行多重派生时
 * 若虚基类没有缺省的构造函数
 * 则在每一个派生类的构造函数中都必须有对虚基类构造函数的调用 
 * 且首先调用
 */
class TC: public virtual Base {
public:
    int t;
    TC();
    TC(int show);
}; 

class HC: public virtual Base {
public:
    int h;
    HC();
    HC(int show);
};

class HTC: public HC, public TC {
public:
    int ht;
    HTC();
    HTC(int show);
};


int main() {
    SC sc1(1);
    sc1.testPublic();
    CC cc2(2);
    cc2.testPrivate();
    XC xc1(1);
    xc1.sameName();
    // 构造函数的调用顺序
    /* 1. 基类的构造函数
     * 2. 对象成员的构造函数
     * 3. 派生类的构造函数（自己的最后调用）
     * 析构顺序相反
     * 上面语句的执行结果：
     * Base calling consruct function 1
     * RC calling construct function 1
     * SC calling construct function 1
     * CC calling construct function 1
     * XBase calling construct function 1
     * XC calling construct function 1
     */

    // 基类、派生类的赋值兼容规则
    /* 1. 只能将派生类对象赋值给基类
     * 2. 可以将派生类对象的地址赋给基类指针
     * 3. 派生类对象可以初始化基类引用
     */
    // 赋值后，基类不包含派生类独有的成员
    Base b, *bp;
    b = sc1;
    bp = &sc1;
    Base &br = sc1;

    HTC htc1(3);
    /* 从gdb可见htc只有一份虚基类Base的拷贝
    (gdb) print htc1
    $1 = {<HC> = {<Base> = {p = 0, n = 1999393856},
        _vptr.HC = 0x4064bc <vtable for HTC+12>, h = 3}, <TC> = {
        _vptr.TC = 0x4064c8 <vtable for HTC+24>, t = 3}, ht = 0}
     */





    
    return 0;
}

// HTC
HTC::HTC():HC(), TC(), ht(h+t) {
    ;
}

HTC::HTC(int show):HC(show), TC(show), ht(h-t) {
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

void XC::sameName() {
    cout << this->Base::n;
    cout << '\t' << this->XBase::n << endl;
    // 下面的语句是非法的，因为XC类中没有n成员，而两个基类中的n成员互相冲突
    //cout << this->n << endl;
}

// CC
CC::CC():SC() {
    ;
}

CC::CC(int show):SC(show) {
    cout << "CC calling construct function " << show << endl;
}

void CC::testPrivate() {
    cout << this->y << '\t';
    cout << this->z << endl;
}

// SC
void SC::testPublic() {
    //cout << this->x << '\t'; // error
    cout << this->y << '\t' << this->z <<endl;
}

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
