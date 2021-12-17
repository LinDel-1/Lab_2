#include "Matrix_utilities.h"
#include "Matrix_utilites_additional.h"
#include "Allocator_other.h" // другой алокатор, для проверки работы с другим (а не тем, что по умолчанию)

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <string>

// методы и функции на матрицы
void test_1(){
    Matrix<int> E { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };
    Matrix<int> m1 { {1, 2, 3}, {4, 5, 6},{7, 8, 9}};
    Matrix<int> m2 { {1, 2, 0}, {0, 33, 0},{0, 0, 4}};
    Matrix<> m3 { {0.0, 2.3, 0.0}, {0.0, 33.2, 0.0},{0.0, 0.0, 4.1}};
    Matrix<int> m4 { {0, 4, 0}, {0, 3, 0},{0, 0, 0}};
    Matrix<int> m5 { {13, 4, 0}, {0, 3, 0},{0, 0, -8}};
    Matrix<double> m6 { {13.0, 4.0, 0.0}, {0.0, 3.0, 0.0},{0.0, 0.0, -8.0}};


    cout << m1  << m1.minor(0,0);

    cout << "m2.det()"<< std::endl;
    cout << m2.det()<< std::endl;

    cout <<"m4" << endl << m4 << "m4.rank()" << std::endl;
    cout << m4.rank() << std::endl;

    cout << "m5.norm()" << std::endl;
    cout << m5.norm() << std::endl<< std::endl;

    cout <<" E.norm()"<< std::endl;
    cout << E.norm()<< std::endl<< std::endl;

    cout << "E.trace()"<< endl;
    cout << E.trace()<< endl<< std::endl;

    cout << "transpose(m1)" << endl;
    cout << transpose(m1);

    cout<< "inv(m5);" << endl;
    cout<< inv(m5) <<"m5 * inv(m5)"<<endl<< m5 * inv(m5);

    cout<< "pow (m5, 3)" << endl << pow (m5, 3)<< endl << "m5 * m5 * m5"<< endl << m5 * m5 * m5<< endl;
}

// сравнение матриц ==
void test_2(){
    Matrix<int> m5 { {13, 4, 0}, {0, 3, 0},{0, 0, -8}};
    Matrix<double> m6 { {13.0, 4.0, 0.0}, {0.0, 3.0, 0.0},{0.0, 0.0, -8.0}};
    Matrix<double> m7 { {13.1, 4.0, 0.0}, {0.0, 3.0, 0.0},{0.0, 0.0, -8.0}};

    cout  << "result of int(m5 == m6):"<< int(m5 == m6)<< endl;
    cout  << "result of int(m5 == m7):"<< int(m5 == m7)<< endl;

    cout << "result of inv(transpose(m6)) == transpose(inv(m6)):" << int (inv(transpose(m6)) == transpose(inv(m6)))<< endl;

    cout << "result of int (inv(m6 * m5) == inv(m6) * inv(m5))):"<< int (inv(m6 * m5) == inv(m6) * inv(m5))<< endl;};

//  методы и функции на вектора
void test_3(){
    Matrix<int> m1  {1, 1, 1};
    Matrix<> m2  {1.1, 2.2, 3.3};

    cout << "m1.norm()"<< std::endl;
    cout << m1.norm()<< std::endl;

    cout << "angle(m1, m2)"<< std::endl;
    cout << angle(m1, m2)<< std::endl;

    cout << "multy_vector(m1, m2)"<< std::endl;
    cout << multy_vector(m1, m2)<< std::endl;

    cout << "multy_scalar(m1, m2)"<< std::endl;
    cout << multy_scalar(m1, m2)<< std::endl;

    cout << "unit(m1)"<< std::endl;
    cout << unit(m1)<< std::endl;

};

// СЛАУ
void test_4(){
    Matrix<int> vec1  {1, 1, 1};
    Matrix<int> E { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };

    cout  << "solve (E, m1):" << endl << solve (E, vec1)<< endl;

    Matrix<int> vec2  {1, 2, 3};
    Matrix<int> m1 { {1, 2, 3}, {4, 1, 0}, {0, 0, 8} };

    cout  << "solve (E, m1):" << endl << solve (m1, vec2)<< endl;

};

// ошибки
void test_5(){
    Matrix<int> m1 { {1, 0},{ 0, 0},{ 1, 0} };
    Matrix<int> m2 { {1, 0, 0}, {0, 0, 0}, {0, 0, 0} };
    Matrix<int> m3 { {1, 0}, {0, 5} };
    Matrix<int> E { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };
    Matrix<int> vec { 1,2,3};
    Matrix<int> vec2 { 1,2};
//
//    m1.det();
//
//    m1.minor(0,6);
//    m1.minor(6,0);
//
//    m1.trace();
//
//    inv(m1);
//    inv(m2);

//    solve(E, m1);// не вектор
//    solve(m3,vec);// разные размеры матрицы и вектора
//    solve(m2,vec); // det = 0
//    solve(m1,vec);// не квадратная матрица

//    m1 == m2;

//    norm(m1); // это норма для вектора!!! m1.norma для матрицы

//    multy_scalar(m1, vec);
//    multy_scalar(vec, m1);
//    multy_scalar(vec, vec2);

//    multy_vector(m1, vec);
//    multy_vector(vec, m1);
//    multy_vector(vec, vec2);
//    multy_vector(vec2, vec);

//    unit(m1);
};

void test_6();
void test_7();