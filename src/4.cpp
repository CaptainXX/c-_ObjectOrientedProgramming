// 第四章：构造函数和析构函数
#include <iostream>
#include <cstring>
using namespace std;
// 20190611进度，第四章，ppt 26
// 20190612进度，第四章，ppt 40

class C {
private:
    int c;
public:
    C(){
        c = 0;
        cout << "C calling construct function.\n";
    }
    C(int x):c(x){
        cout << "C calling construct function.\n";
    }
};

class A {
    class B {
        int a;
    public:
        B(){
            cout << "B calling construct function\n";
        };
        B(int x):a(x){};
        void set(int x) {
            this->a = x;
        }
    };
    int mem0;

private:
    // 对象成员的构造函数调用顺序取决于说明顺序，与构造函数初始化列表中的顺序无关
    C c1;
    B B1, B2;
    int mem1;
    int *ptrA;
    char *strA;
protected:
    int mem2;
public: 
    int mem3;
    /* 缺省构造函数的说明
     * 1. 类中定义了没有参数的构造函数，或形参全有缺省值的构造函数，均称为缺省构造函数
     * 2. 缺省构造函数只能有一个
     * 3. 产生对象时，必定调用构造函数
     * 4. 对象的构造函数是唯一的，在定义对象时确定
     */
    A(){
        cout << "Default construct function.\n";
    } // 如果不定义构造函数，则类有此形式的**缺省构造函数**
    // 构造函数，初始化对象
    /*
     * 1. 构造函数名与类名相同
     * 2. 不能指定构造函数的返回值类型
     * 3. 一个类可以定义多个构造函数，即构造函数的重载
     * 4. 构造函数参数可以指定缺省值
     * 5. 要注意构造函数的权限：
     *   1. 要使用构造类的对象时，构造函数必须是public
     *   2. 类仅用于派生其他类时，可以将构造函数定义为protected
     */
    // 带**缺省值**的构造函数
    A(int m1, int m2, int m3, int m4, int b1, int b2 = 1):mem0(m1), mem1(m2), mem2(m3), mem3(m4), B1(b1), B2(b2), c1(m1){};
    // 这里c1在初始化列表的最后，但是对象成员声明时，它在B类的对象之前，所以还是先调用C的构造函数
    A(int m1, int m2, int m3, int m4):mem0(m1), mem1(m2), mem2(m3), mem3(m4), B1(m1), B2(m2), c1(m1){};
    A(int show);
    A(char* s) {
        cout << "A constructing a string...\n";
        this->strA = new char[strlen(s)+1];
        strcpy(this->strA, s);
        cout << this->strA << endl;
    }
    // 拷贝构造函数
    // 如果没有定义拷贝构造函数，系统会产生缺省的拷贝构造函数
    // 如果数据成员需要使用new运算符，则必须显式地定义一个拷贝构造函数
    /* 拷贝构造函数的调用
     * 1. 变量声明时，用一个对象初始化另一个对象时
     * 2. 对象作为实参，传递给函数的形参时
     * 3. 对象是函数的返回值时
     */
    A(const A& a);
    /* 析构函数
     * 析构函数的使用时机：当对象使用了new运算符时，必须在析构函数中使用delete来释放内存
     * 1. 在对象生命期结束时调用，释放空间
     * 2. 不能带：参数、返回值、函数类型
     * 3. 不允许重载
     * 4. 对象撤销时由操作系统自动调用
     * 
     */
    ~A(){
        cout << "A calling destruct function\n";
        if (this->ptrA)
            delete this->ptrA;
        // 如果指针是空值，使用delete运算符会产生段错误！
        char* s = (char*)0x20; // 0x20为本机默认空字符串地址，更换环境后可能会不同
        if (this->strA != s)
            delete[] this->strA;
    }
    void setMems(int, int, int, int );
    void setMems(int, int, int, int, int, int b = 0);
    void getMems(int*, int*, int*, int*);
    void getMemsByRef(int&, int&, int&, int&);
    int &returnRef();
    friend ostream &operator<<(ostream&, A&);
}; 

/* 1. 局部对象，每次定义时都会调用构造函数
 * 2. 静态对象，首次定义时调用一次构造函数
 * 3. 全局对象，在main函数执行前调用构造函数
*/
A a1(1);

A::A(int show) {
    cout << "A calling construct function " << show << endl;
    this->ptrA = new int;
    *ptrA = 10;
};

A::A(const A& a) {
    cout << "A calling copy construct function.\n";
    this->mem0 = a.mem0;
    this->mem1 = a.mem1;
    this->mem2 = a.mem2;
    this->mem3 = a.mem3;
}

void constructA() {
    A a2(2);
}

void constructStaticA() {
    static A a3(3);
}

// 动态构建和析构对象数组
void objectArray() {
        A *pa;
        pa = new A[3];
        delete[] pa;
}

// 以类为形参并返回类的函数
A foo(const A& a) {
    return a;
}

int main() {
    cout << "Enter main\n";
    //objectArray();
    // 缺省构造函数不对对象的成员赋值，所以值是不确定的
    A x;
    cout << x;
    constructA();
    constructStaticA();
    constructA();
    constructStaticA();
    // new
    cout << "使用new动态产生对象：\n";
    A *pa;
    pa = new A(1, 2, 3, 4);
    cout << *pa;
    A s("hello, world!");
    cout << "使用拷贝构造函数：\n";
    A a2(*pa);
    // 拷贝构造函数的三种调用时机
    // 可以使用gdb查看调用细节
    A a3 = *pa;         // 1. 声明
    foo(a3); // 2. 类为形参 3. 返回类的对象
    cout << a2;
    delete pa; // new 和 delete 必须成对使用，否则会造成内存泄漏
    return 0;
}




A a4(4);
ostream& operator<<(ostream& os, A& a) {
    os << a.mem0 << ' '  << a.mem1 << ' '  << a.mem2 << ' '  << a.mem3;
    cout << endl;
    return os; 
}

int& A::returnRef() {
    return mem0;
}

void A::setMems(int a1, int a2, int a3, int a4) {
    this->mem0 = a1;
    this->mem1 = a2;
    this->mem2 = a3;
    this->mem3 = a4;
}

void A::getMems(int* m1, int* m2, int* m3, int* m4) {
    *m1 = this->mem0;
    *m2 = this->mem1;
    *m3 = this->mem2;
    *m4 = this->mem3;
}

void A::getMemsByRef(int& m1, int& m2, int& m3, int& m4) {
    m1 = this->mem0;
    m2 = this->mem1;
    m3 = this->mem2;
    m4 = this->mem3;
}

void A::setMems(int a1, int a2, int a3, int a4, int b1, int b2) {
    this->mem0 = a1;
    this->mem1 = a2;
    this->mem2 = a3;
    this->mem3 = a4;
    this->B1.set(b1);
    this->B2.set(b2);
}