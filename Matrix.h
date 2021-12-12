#pragma once

#include<iostream>
#include"Allocator.h"

template<typename T = double, typename Alloc=Allocator<T>>
class Matrix {
public:
	template<typename Other, typename Alloc_Other> friend class Matrix; // ����������� � ������ ���������, ����� ������������ �� ��������������

	// ��������� �����������
	explicit Matrix() noexcept {}

	// ����������� � 2 ����������� (�������) c 1 ���������� (������)
	explicit Matrix(const size_t rows, const size_t columns = 1, Alloc alloc = Alloc()); 

	// ���������������� ������ (������������ �������)
	template<typename Other> 
	Matrix(std::initializer_list<Other> init_list, Alloc alloc = Alloc());

	// ���������������� ������� initializer_list ��������� �� initializer_list
	template<typename Other> 
	Matrix(std::initializer_list<std::initializer_list<Other>> init_list, Alloc alloc = Alloc());

	// ����������� �����������
	Matrix(const Matrix& object);

	// ����������� ����������� �� ������� ������� ����
	template<typename Other, typename Alloc_Other> 
	Matrix(const Matrix<Other, Alloc_Other>& object);

	// ������������ �����������
	Matrix(Matrix&& object) noexcept; 

	// ����������
	~Matrix() noexcept; 

	// �������� ������������ ����������
	Matrix& operator = (const Matrix& object);	

	// �������� ������������ ���������� �� ������� ������� ����
	template<typename Other, typename Alloc_Other>
	Matrix& operator = (const Matrix<Other, Alloc_Other>& object);

	// �������� ������������ ������������
	Matrix& operator = (Matrix&& object) noexcept;	
	
	// �������� �������������� ������������ c �������� ������� ����
	template<typename Other, typename Alloc_Other>  
	Matrix& operator += (const Matrix<Other, Alloc_Other>& object);

	// �������� �������������� ��������� c �������� ������� ����
	template<typename Other, typename Alloc_Other>  
	Matrix& operator -= (const Matrix<Other, Alloc_Other>& object);

	// �������� �������������� ��������� �� ����� ������� ����
	template<typename Other>  
	Matrix& operator *= (const Other& value);

	// �������� �������������� ��������� �� ������� ������� ����
	template<typename Other, typename Alloc_Other>
	Matrix& operator *= (const Matrix<Other, Alloc_Other>& object);

	// ������� ��������� �������� � ���������:
	Matrix& operator + () { return *this; }
	Matrix operator - () { return Matrix(*this) *= -1; }
	
	size_t get_columns() const noexcept { return m_columns; }
	size_t get_rows() const noexcept { return m_rows; }
	size_t size() const noexcept { return m_columns * m_rows; } // ���������� ���������� ��������� �������
	size_t capacity() const noexcept { return m_capacity; } // ����������� �������

	T& operator() (size_t row, size_t column); // �������� ������ ������� (��������� ��� ��������� ����� [i][j])
	const T& operator() (size_t row, size_t column) const; // �������� ������ ������� ��� ����������� �������

private:
	T* m_ptr = nullptr;
	size_t m_rows = 0, m_columns = 0;
	size_t m_capacity = 0;
	Alloc m_alloc = {};
};

#include "Matrix.hpp" // ��� ��������� ��� ����������
