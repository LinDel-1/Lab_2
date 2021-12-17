//
// Matrix class declaration
//

#pragma once             // Header guard (anti multiple including)
#include <memory>        // Working with embedded pointer-based template classes
#include "Allocator.h"   // Instrument for memory allocation
#include <string>        // Operating strings (in operator <<)
#include <iomanip>       // Format output (std::setw)

using namespace std;

template <typename T, typename Alloc = Allocator<T>>
class MyMatrix{
public:
    explicit MyMatrix(size_t rows = 1, size_t cols = 1, Alloc alloc = Alloc());                  // Constructor with params
    MyMatrix(const MyMatrix& object);                                                            // Copy constructor
    MyMatrix(MyMatrix&& object) noexcept;                                                        // Move constructor
    ~MyMatrix();                                                                                 // Destructor

    // Template constructors
    template <typename T_1>
    MyMatrix(const MyMatrix<T_1>& object);                                                       // Copy constructor (from another type)
    template<typename T_1>
    MyMatrix(const initializer_list<T_1>& init_list, Alloc alloc = Alloc());                     // List-of-T_1 constructor
    template<typename T_1>
    MyMatrix(const initializer_list<initializer_list<T_1>>& init_list, Alloc alloc = Alloc());   // List-of-lists constructor

    template <typename T_1, typename Alloc_1> friend class MyMatrix;                             // Declaring other instantiations as friends

    void swap(MyMatrix& object) noexcept;                                                        // Swap method
    MyMatrix& operator = (const MyMatrix& object);                                               // Copy assignment
    MyMatrix& operator = (MyMatrix&& object) noexcept;                                           // Move assignment
    T& operator () (int num_row, int num_col);                                                   // L-value indexing
    const T& operator () (int num_row, int num_col) const;                                       // R-value indexing

    template <typename T_1, typename Alloc_1 = Allocator<T_1>>
    MyMatrix& operator = (const MyMatrix<T_1, Alloc_1>& object);                                 // Copy assignment (from another type)

    // Algebraic assignments
    template <typename T_1>
    MyMatrix& operator *= (const MyMatrix<T_1>& object);
    template <typename Scalar>
    MyMatrix& operator *= (Scalar scalar);
    template <typename T_1>
    MyMatrix& operator += (const MyMatrix<T_1>& object);
    template <typename T_1>
    MyMatrix& operator -= (const MyMatrix<T_1>& object);

    // Comparison operators
    template <typename T_1>
    bool operator == (const MyMatrix<T_1>& object);
    template <typename T_1>
    bool operator != (const MyMatrix<T_1>& object);

    // Additional numpy-like methods
    MyMatrix flatten();
    MyMatrix reshape(int new_rows, int new_cols);

    // Friend functions
    template <typename T_1>
    friend std::ostream& operator << (std::ostream &out, const MyMatrix<T_1>& object);
    template <typename T_1, typename T_2>
    friend MyMatrix<decltype(T_1() + T_2())> operator + (const MyMatrix<T_1>& obj_1, const MyMatrix<T_2>& obj_2);
    template <typename T_1, typename T_2>
    friend MyMatrix<decltype(T_1() + T_2())> operator - (const MyMatrix<T_1>& obj_1, const MyMatrix<T_2>& obj_2);
    template <typename T_1, typename T_2>
    friend MyMatrix<decltype((T_1() * T_2()) + (T_1() * T_2()))> operator * (const MyMatrix<T_1>& obj_1, const MyMatrix<T_2>& obj_2);
    template <typename Scalar, typename T_1>
    friend MyMatrix<decltype(Scalar() * T_1())> operator * (Scalar scalar, const MyMatrix<T_1>& object);
    template <typename T_1, typename Scalar>
    friend MyMatrix<decltype(T_1() * Scalar())> operator * (const MyMatrix<T_1>& object, Scalar scalar);
    template<typename T_1> friend struct TextMode<T_1>;

private:
    int m_rows;                  // Number of rows
    int m_cols;                  // Number of columns
    Alloc m_alloc;               // Allocator object (as a toolkit with memory-functions)
    T* m_arr = nullptr;          // Data resource (array of template type)
};

#include "Streamwork.h"