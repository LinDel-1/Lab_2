#include <iostream>
#include "MyMatrix_.h"
#include <string>

#define TEST 10

using namespace std;

int main() {
#if TEST == 2
    cout << "----------------- Test 2 ------------------" << endl;
    MyMatrix<int> m1(4);
    cout << m1;
    MyMatrix<int> m2(5, 3);
    MyMatrix<int> m3(m2);
    //MyMatrix<int> m4(move(m1));
    m3(0, 0) = 15;
    cout << m2;
    cout << m3;
    //cout << m4;
    MyMatrix<int> m5 = { {1, 2, 3}, {4, 5, 6} };
    MyMatrix<int> m6 = { {1, 2, 3, 4, 5, 6} };
    MyMatrix<int> m7 = { 1, 2, 3, 4, 5, 6 };
    MyMatrix<int> m8 = { {1},{2},{3},{4},{5},{6} };
    /*
    cout << m5;
    cout << m6;
    cout << m7;
    cout << m8;*/
#elif TEST == 3
    cout << "----------------- Test 3 ------------------" << endl;
    MyMatrix<int> m9(4);
    cout << m9;
    MyMatrix<int> m10 = { {1, 2, 3}, {4, 5, 6} };
    m9 = m10;
    cout << m9;
    m9 = MyMatrix<int>{ 1, 2, 3, 4, 5, 6 };
    cout << m9;
#elif TEST == 4
    cout << "----------------- Test 4 ------------------" << endl;
    MyMatrix<int> m11 = { {1, 2, 3}, {4, 5, 6} };
    cout << m11;
    int val = m11(0,2);      // => 3 т.к. это 1-ая строка, 3-ий элемент
    cout << "val = m(0, 2) = " << val << endl;
    m11(0,2) = 7;            // теперь 1-ая строка, 3-ий элемент стал равен 7
    cout << m11;
    const MyMatrix<int> c_m = { {1, 2, 3}, {4, 5, 6} };
    int val_1 = c_m(0,2);  // => 3 т.к. это 1-ая строка, 3-ий элемент
    //c_m(0,2) = 7;          // ОШИБКА т.к. нельзя менять константную матрицу
#elif TEST == 5
    cout << "----------------- Test 5 ------------------" << endl;
    MyMatrix<int> A = {{1, 2, 3}, {4, 5, 6}, {0, 0, 1}};
    MyMatrix<double> B = {{1, 9, 0}, {0, 1, 1}, {1, 4, 2}};
    cout << "A:\n" << A;
    cout << "B:\n" << B;
    cout << "A + B:\n"<< A + B;
    cout << "A - B:\n"<< A - B;
    cout << "A * B:\n"<< A * B;
    A *= B;          // <= Switch operations as you want
    cout << "Arithmetical assignment operator:\n"<< A;
#elif TEST == 8
    cout << "----------------- Test 8 ------------------" << endl;
    MyMatrix<double> m_d = { {1, 2}, {3, 4}, {5, 74}};
    MyMatrix<int> m_i = { {1.1, 2.2, 3.3}, {4.4, 5.5, 6.6} };
    cout << "m_d:\n" << m_d;
    cout << "m_i:\n" << m_i;
    MyMatrix<short> m_s = m_d;
    cout << "m_s:\n" << m_s;
    cout << "m_s = m_i:\n" << (m_s = m_i);
    cout << "m_s += m_i:\n" << (m_s += m_i);
    cout << "m_s -= m_i:\n" << (m_s -= m_i);
    cout << "m_s *= 3.14:\n" << (m_s *= 3.14);
    cout << "m_s + m_i - m_s:\n" << (m_s + m_i - m_s);
    cout << "m_d * m_i:\n" << (m_d * m_i);
    cout << "m_d * 0:\n" << (m_d * 0);
    cout << "3.14 * m_i:\n" << (3.14 * m_i);
#elif TEST == 9
    MyMatrix<int> A = {{1, 2, 3}, {3, 4, 5}, {7, 8, 9}, {10, 11, 12}};
    cout << "A:\n" << A;
    cout << "A.flatten():\n" << A.flatten();
    cout << "A.reshape(2, 6):\n" << A.reshape(2, 6);
#endif

    MyMatrix<int> A = {{1, 2}, {3, 4}};
    MyMatrix<double> B = {{1, 0}, {0, 1}};
    A -= B;
    cout << A;
    return 0;
}
