// 第三章：类和对象
#include <iostream>
using namespace std;
// 类的定义
class A {
    // 类的嵌套定义
    class B {
        int a;
    public:
        B(){};
        B(int x):a(x){};
        void set(int x) {
            this->a = x;
        }
    };
    // 不加限制词的成员默认为private
    int mem0;
    // extern int a;    // 定义类成员时不能使用关键字（auto register）
    //int a = 1;        // 定义类成员时不能初始化

private:    // 只允许该类访问
    B B1, B2;
    int mem1;
protected:  // 该类和它的派生类可用 
    int mem2;
public:     // 类内类外都能使用
    int mem3;
    A(){};
    A(int m1, int m2, int m3, int m4):mem0(m1), mem1(m2), mem2(m3), mem3(m4), B1(m1), B2(m2){};
    void setMems(int, int, int, int );                      // 私有成员需要通过成员函数访问，
    void setMems(int, int, int, int, int, int b = 0);      // 成员函数重载，通过类型和数目区分，并且可以带有缺省值，缺省值必须从形参表右边开始
    void getMems(int*, int*, int*, int*);                   // 通过指针获取类私有成员的值
    void getMemsByRef(int&, int&, int&, int&);             // 通过引用获取私有成员的值
    int &returnRef();                                       // 返回引用类型的成员函数
    friend ostream &operator<<(ostream&, A&);
}; // 分号很重要

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

int main() {
    A a1;
    cout << "Set members: 1234\n";
    a1.setMems(1, 2, 3, 4);
    cout << "Get members:";
    int q, w, e, r;
    a1.getMems(&q, &w, &e, &r);
    cout << q << ' ' << w << ' ' << e << ' ' << r << endl;
    cout << a1;

    int x = 10;
    a1.returnRef() = x;
    cout << a1;
    a1.getMemsByRef(q, w, e, r);
    cout << q << ' ' << w << ' ' << e << ' ' << r << endl;
    class C{ // 局部对象
        int mem0;
    };
    return 0;
}
