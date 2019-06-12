#include <iostream>
using namespace std;

void test(){
    cout << '1' << endl;
}

int main(){
    test();
    // 第一部分：行指针
    int x[3][4] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 0, 1, 2
        };
    cout << "x[3][4]: {1 2 3 4}{5 6 7 8}{9 0 1 2}\n";
    cout << "x = " << x << endl;
    cout << "x[0] = " << x[0] << endl;
    cout << "x + 1 = " << x + 1 << endl;
    cout << "x[1] = " << x[1] << endl;
    cout << "*(x[0]+1) = " << *(x[0]+1) << endl;
    cout << "x[0][1] = " << x[0][1] << endl;
    cout << "review end.\n";
    return 0;
}