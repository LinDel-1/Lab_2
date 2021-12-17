//
// MyMatrix class implementation
//

#pragma once
#include "MyMatrix.h"

using namespace std;

template <typename T, typename Alloc>
MyMatrix<T, Alloc>::MyMatrix(size_t rows, size_t cols, Alloc alloc) : m_alloc(alloc){
    if(rows <= 0 || cols <= 0){
        throw runtime_error("Matrix with zero/negative number of rows/columns!");
    }
    T* temp_arr = m_alloc.allocate(rows * cols);
    size_t i = 0;
    try {
        while (i < rows * cols) {
            m_alloc.construct(temp_arr + i);       // Launching default constructors
            ++i;
        }
    }
    catch (...) {
        size_t k = 0;
        while (k <= i) {
            m_alloc.destroy(temp_arr + i);         // Launching destructors
            ++k;
        }
        m_alloc.deallocate(temp_arr);              // Free memory
        throw;                                     // Throwing exception farther
    }
    m_rows = rows;
    m_cols = cols;
    m_arr = temp_arr;
}

template <typename T, typename Alloc>
template<typename T_1>
MyMatrix<T, Alloc>::MyMatrix(const std::initializer_list<T_1>& init_list, Alloc alloc) : m_alloc(alloc) {
    T* temp_arr = m_alloc.allocate(init_list.size());
    size_t i = 0;
    try {
        for (auto c_it = std::cbegin(init_list); c_it != std::cend(init_list); ++c_it) {
            m_alloc.construct(temp_arr + i, *c_it);
            ++i;
        }
    }
    catch (...) {
        size_t k = 0;
        while (k <= i) {
            m_alloc.destroy(temp_arr + i); // запуск деструкторов
            ++k;
        }
        m_alloc.deallocate(temp_arr); // освободим память
        throw; // прокинем исключение дальше
    }
    m_rows = 1;
    m_cols = init_list.size();
    m_arr = temp_arr;
}

template <typename T, typename Alloc>
template <typename T_1>
MyMatrix<T, Alloc>::MyMatrix(const initializer_list<initializer_list<T_1>>& init_list, Alloc alloc) : m_alloc(alloc) {
    for(auto c_it = std::cbegin(init_list); c_it != std::cend(init_list); ++c_it){
        if(c_it->size() != init_list.begin()->size()){
            throw runtime_error("Different sizes of rows!");
        }
    }
    T* temp_arr = m_alloc.allocate(init_list.size() * init_list.begin()->size());
    size_t i = 0;
    try {
        for (auto c_it = std::cbegin(init_list); c_it != std::cend(init_list); ++c_it) {
            for(auto cc_it = std::cbegin(*(c_it)); cc_it != std::cend(*(c_it)); ++cc_it){
                m_alloc.construct(temp_arr + i, *cc_it);
                ++i;
            }
        }
    }
    catch (...) {
        size_t k = 0;
        while (k <= i) {
            m_alloc.destroy(temp_arr + i); // запуск деструкторов
            ++k;
        }
        m_alloc.deallocate(temp_arr); // освободим память
        throw; // прокинем исключение дальше
    }
    m_rows = init_list.size();
    m_cols = init_list.begin()->size();
    m_arr = temp_arr;
}


template <typename T, typename Alloc>
MyMatrix<T, Alloc>::MyMatrix(const MyMatrix& object) : m_alloc(object.m_alloc){
    T* temp_arr = m_alloc.allocate(object.m_rows * object.m_cols);
    size_t i = 0;
    try {
        while (i < object.m_rows * object.m_cols) {
            m_alloc.construct(temp_arr + i, object.m_arr[i]);
            ++i;
        }
    }
    catch (...) {
        size_t k = 0;
        while (k <= i) {
            m_alloc.destroy(temp_arr + i);
            ++k;
        }
        m_alloc.deallocate(temp_arr);
        throw;
    }
    m_rows = object.m_rows;
    m_cols = object.m_cols;
    m_arr = temp_arr;
}


template <typename T, typename Alloc>
template <typename T_1>
MyMatrix<T, Alloc>::MyMatrix(const MyMatrix<T_1>& object) : m_alloc(object.m_alloc){
    cout << "Copy costructor from another type" << endl;
    T* temp_arr = m_alloc.allocate(object.m_rows * object.m_cols);
    size_t i = 0;
    try {
        while (i < object.m_rows * object.m_cols) {
            m_alloc.construct(temp_arr + i, object.m_arr[i]);
            ++i;
        }
    }
    catch (...) {
        size_t k = 0;
        while (k <= i) {
            m_alloc.destroy(temp_arr + i); // запуск деструкторов
            ++k;
        }
        m_alloc.deallocate(temp_arr);
        throw;
    }
    m_rows = object.m_rows;
    m_cols = object.m_cols;
    m_arr = temp_arr;
}


template <typename T, typename Alloc>
MyMatrix<T, Alloc>::MyMatrix(MyMatrix&& object) noexcept : m_alloc(object.m_alloc), m_rows(0), m_cols(0), m_arr(nullptr){
    swap(object);
}


template <typename T, typename Alloc>
MyMatrix<T, Alloc>::~MyMatrix(){
    for (size_t i = 0; i < m_rows * m_cols; ++i)
        m_alloc.destroy(m_arr + i);
    m_alloc.deallocate(m_arr);
}

template <typename T, typename Alloc>
void MyMatrix<T, Alloc>::swap(MyMatrix& object) noexcept {
    std::swap(m_rows, object.m_rows);
    std::swap(m_cols, object.m_cols);
    std::swap(m_arr, object.m_arr);
    std::swap(m_alloc, object.m_alloc);
}

template <typename T, typename Alloc>
MyMatrix<T, Alloc>& MyMatrix<T, Alloc>:: operator = (const MyMatrix& object){
    if((object.m_arr == m_arr) && (object.m_rows == m_rows) && (object.m_cols == m_cols)){
        cout << "Shortcut assignment (object to itself)" << endl;
        return *this;
    }
    if((object.m_cols * object.m_rows) == (m_cols * m_rows)){
        for(size_t i = 0; i < object.m_cols * object.m_rows; ++i){
            m_arr[i] = object.m_arr[i];
        }
        m_rows = object.m_rows;
        m_cols = object.m_cols;
        return *this;
    }
    MyMatrix temp_matrix(object);
    swap(temp_matrix);
    return *this;
}

template <typename T, typename Alloc>
template<typename T_1, typename Alloc_1>
MyMatrix<T, Alloc>& MyMatrix<T, Alloc>:: operator = (const MyMatrix<T_1, Alloc_1>& object){
    MyMatrix temp_matrix(object);
    swap(temp_matrix);
    return *this;
}


template <typename T, typename Alloc>
MyMatrix<T, Alloc>& MyMatrix<T, Alloc>:: operator = (MyMatrix&& object) noexcept {
    swap(object); // No need to clean the object cos it will be eliminated
    return *this;
}


template <typename T, typename Alloc>
T& MyMatrix<T, Alloc>:: operator () (int num_row, int num_col){
    if((num_row >= m_rows) || (num_col >= m_cols) || (num_row < 0) || (num_col < 0)){
        throw runtime_error("Matrix index out of range!");
    }
    return m_arr[m_cols * num_row + num_col];
}

template <typename T, typename Alloc>
const T& MyMatrix<T, Alloc>:: operator () (int num_row, int num_col) const {
    if((num_row >= m_rows) || (num_col >= m_cols) || (num_row < 0) || (num_col < 0)){
        throw runtime_error("Matrix index out of range!");
    }
    return m_arr[m_cols * num_row + num_col];
}

template <typename T, typename Alloc>
template <typename Scalar>
MyMatrix<T, Alloc>& MyMatrix<T, Alloc>:: operator *= (Scalar scalar){
    for(int i = 0; i < m_rows; i++){
        for(int j = 0; j < m_cols; j++){
            m_arr[m_cols * i + j] *= scalar;
        }
    }
    return *this;
}

template <typename T, typename Alloc>
template <typename T_1>
MyMatrix<T, Alloc>& MyMatrix<T, Alloc>:: operator += (const MyMatrix<T_1>& object){
    if((m_rows != object.m_rows) || (m_cols != object.m_cols)){
        throw runtime_error("Sizes of matrices doesn't match!");
    }
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < m_cols; j++){
            (*this)(i, j) += object(i, j);
        }
    }
    return *this;
}

template <typename T, typename Alloc>
template <typename T_1>
MyMatrix<T, Alloc>& MyMatrix<T, Alloc>:: operator -= (const MyMatrix<T_1>& object){
    if((m_rows != object.m_rows) || (m_cols != object.m_cols)){
        throw runtime_error("Sizes of matrices doesn't match!");
    }
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < m_cols; j++){
            (*this)(i, j) -= object(i, j);
        }
    }
    return *this;
}

template <typename T, typename Alloc>
template <typename T_1>
bool MyMatrix<T, Alloc>:: operator == (const MyMatrix<T_1>& object){
    if ((typeid(*this).name() != (typeid(object).name()))){
        return false;
    } else if ((m_rows == object.m_rows) && (m_cols == object.m_cols)){
        for(size_t i = 0; i < m_rows * m_cols; i++){
            if(m_arr[i] != object.m_arr[i]){
                return false;
            }
        }
        return true;
    }
    return false;
}

template <typename T, typename Alloc>
template <typename T_1>
bool MyMatrix<T, Alloc>:: operator != (const MyMatrix<T_1>& object){
    return !(*this == object);
}

template <typename T, typename Alloc>
template <typename T_1>
MyMatrix<T, Alloc>& MyMatrix<T, Alloc>:: operator *= (const MyMatrix<T_1>& object){
    if(m_cols != object.m_rows){
        throw runtime_error("Forbidden sizes for matrix multiplication!");
    }
    MyMatrix<T, Alloc> temp_matrix(m_rows, object.m_cols);
    for(int i = 0; i < temp_matrix.m_rows; i++){
        for(int j = 0; j < temp_matrix.m_cols; j++){
            T res = 0;
            for(int k = 0; k < m_cols; k++){
                res += (*this)(i, k) * object(k, j);
            }
            temp_matrix(i, j) = res;
        }
    }
    (*this) = std::move(temp_matrix);
    return (*this);
}

template <typename T, typename Alloc>
MyMatrix<T, Alloc> MyMatrix<T, Alloc>::flatten() {
    MyMatrix temp_matrix(*this);
    int temp_rows = temp_matrix.m_rows;
    temp_matrix.m_rows = 1;
    temp_matrix.m_cols *= temp_rows;
    return temp_matrix;
}

template <typename T, typename Alloc>
MyMatrix<T, Alloc> MyMatrix<T, Alloc>:: reshape(int new_rows, int new_cols){
    if((new_rows < 0) || (new_cols < 0) || (m_rows * m_cols != new_rows * new_cols)){
        throw runtime_error("Unsuitable parameters to reshape the matrix.");
    }
    MyMatrix temp_matrix(*this);
    temp_matrix.m_rows = new_rows;
    temp_matrix.m_cols = new_cols;
    return temp_matrix;
}

// Friend functions for MyMatrix class
template <typename T_1, typename T_2>
MyMatrix<decltype(T_1() + T_2())> operator + (const MyMatrix<T_1>& obj_1, const MyMatrix<T_2>& obj_2){
    if((obj_1.m_rows != obj_2.m_rows) || (obj_1.m_cols != obj_2.m_cols)){
        throw runtime_error("Sizes of matrices doesn't match!");
    }
    MyMatrix<decltype(T_1() + T_2())> temp_matrix(obj_1.m_rows, obj_2.m_cols);
    for(int i = 0; i < obj_1.m_rows; i++){
        for(int j = 0; j < obj_1.m_cols; j++){
            temp_matrix(i, j) = obj_1(i, j) + obj_2(i, j);
        }
    }
    return temp_matrix;
}

template <typename T_1, typename T_2>
MyMatrix<decltype(T_1() + T_2())> operator - (const MyMatrix<T_1>& obj_1, const MyMatrix<T_2>& obj_2){
    if((obj_1.m_rows != obj_2.m_rows) || (obj_1.m_cols != obj_2.m_cols)){
        throw runtime_error("Sizes of matrices doesn't match!");
    }
    MyMatrix<decltype(T_1() + T_2())> temp_matr(obj_1.m_rows, obj_2.m_cols);
    for(int i = 0; i < obj_1.m_rows; i++){
        for(int j = 0; j < obj_1.m_cols; j++){
            temp_matr(i, j) = obj_1(i, j) - obj_2(i, j);
        }
    }
    return temp_matr;
}

template <typename T_1, typename T_2>
MyMatrix<decltype((T_1() * T_2()) + (T_1() * T_2()))> operator * (const MyMatrix<T_1>& obj_1, const MyMatrix<T_2>& obj_2){
    if(obj_1.m_cols != obj_2.m_rows){
        throw runtime_error("Forbidden sizes for matrix multiplication!");
    }
    MyMatrix<decltype((T_1() * T_2()) + (T_1() * T_2()))> temp_matrix(obj_1.m_rows, obj_2.m_cols);
    for(int i = 0; i < temp_matrix.m_rows; i++){
        for(int j = 0; j < temp_matrix.m_cols; j++){
            decltype((T_1() * T_2()) + (T_1() * T_2())) res = 0;
            for(int k = 0; k < obj_1.m_cols; k++){
                res += obj_1(i, k) * obj_2(k, j);
            }
            temp_matrix(i, j) = res;
        }
    }
    return temp_matrix;
}

template <typename Scalar, typename T_1>
MyMatrix<decltype(Scalar() * T_1())> operator * (Scalar scalar, const MyMatrix<T_1>& object){
    MyMatrix<decltype(Scalar() * T_1())> temp_matrix = object;
    for(int i = 0; i < temp_matrix.m_rows; i++){
        for(int j = 0; j < temp_matrix.m_cols; j++){
            temp_matrix.m_arr[temp_matrix.m_cols * i + j] *= scalar;
        }
    }
    return temp_matrix;
}

template <typename T_1, typename Scalar>
MyMatrix<decltype(T_1() * Scalar())> operator * (const MyMatrix<T_1>& object, Scalar scalar){
    MyMatrix<decltype(T_1() * Scalar())> temp_matrix = object;
    for(int i = 0; i < temp_matrix.m_rows; i++){
        for(int j = 0; j < temp_matrix.m_cols; j++){
            temp_matrix.m_arr[temp_matrix.m_cols * i + j] *= scalar;
        }
    }
    return temp_matrix;
}

template <typename T_1>
std::ostream& operator << (std::ostream &out, const MyMatrix<T_1>& object) {
    int max_len = 0;
    for (int i = 0; i < object.m_rows * object.m_cols; i++) {
        if (to_string(object.m_arr[i]).length() > max_len) {
            max_len = to_string(object.m_arr[i]).length();
        }
    }
    for (int i = 1; i <= object.m_rows; i++) {
        cout << '|';
        cout << std::setw(max_len + 2) << std::left << object.m_arr[object.m_cols * (i - 1) + 0];
        for (int j = 1; j < object.m_cols; j++) {
            cout << std::setw(max_len + 2) << std::right << object.m_arr[object.m_cols * (i - 1) + j];
            if (j < object.m_cols - 1) cout << " ";
        }
        cout << '|';
        if(i == object.m_rows){
            cout << " (dtype=" << typeid(*(object.m_arr)).name() << ")" << endl;
        }
        cout << endl;
    }
    return out;
}

#include "Streamwork.h"