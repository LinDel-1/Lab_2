#include "Matrix_utilities.h"
#include "Allocator_other.h" // ������ ��������, ��� �������� ������ � ������ (� �� ���, ��� �� ���������)

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <string>

class StrangeClass {
public:
	StrangeClass() { // ��������� ����������� ������ ������ ����������
		throw std::runtime_error("StrangeClass() throwed exception!");
		++count; // �� ����� ������� �� �����
	}
	StrangeClass(double val) { 
		if (count == 2) // �.�. ���� ��� ������ �������, ������ ����������...
			throw std::runtime_error("THIRED StrangeClass(double) throwed exception!");
		cout << "StrangeClass(double) get one parametr: " << val << endl;
		++count;
	}
	~StrangeClass() {
		cout << "~StrangeClass() destroyed element number: " << count << endl;
		--count;
	}
private:
	static size_t count;
};
size_t StrangeClass::count = 0;

void test_init() {
	cout << "-----------------------TEST_INIT-----------------------" << endl;
	Matrix<> m0; // ������ ������� (��� ������-���� ��������� ������)
	cout << m0 << endl;

	Matrix<> m1(4); // ������� ����: 4 ������ � 1 ������� (��� ���������� �������������� ��������� ������������ MyType())
	cout << m1 << endl; // m1 �� double (�.�. �� ���������)

	Matrix<int> m2(4, 6); // ������� ����: 4 ������ � 6 �������� (��� ���������� �������������� ��������� ������������ MyType()) 
	cout << m2 << endl;

	Matrix<int> m3(m2); // ����������� �����������
	cout << m2 << endl;
	cout << m3 << endl;

	Matrix<> m4(m2); // ����������� ����������� ��������� �.�. ������ ����
	cout << m2 << endl;
	cout << m4 << endl;

	Matrix<int> m5(std::move(m2)); // ����������� �����������
	cout << m2 << endl;
	cout << m5 << endl;

	Matrix<> m6(std::move(m5)); // ����������� ����������� ��������� �.�. ������ ����
	cout << m5 << endl;
	cout << m6 << endl;

	Matrix<int> m7 = { {1, 2, 3}, {4, 5, 6} }; // initializer_list ����������� (��� �� ���): ������� ����: 2 ������ � 3 ������� 
	cout << m7 << endl;
	Matrix<int> m8 = { {1, 2, 3, 4, 5, 6} }; // initializer_list ����������� (��� �� ���): ������� ����: 1 ������ � 6 ��������
	cout << m8 << endl;
	Matrix<char> m9 = { 1, 2, 3, 4, 5, 6 }; // initializer_list ����������� (������ ���): ������� ����: 6 ����� � 1 ������� 
	cout << m9 << endl;
	Matrix<char> m10 = { {1}, {2}, {3}, {4}, {5}, {6} }; // initializer_list ����������� (������ ���): ������� ����: 6 ����� � 1 �������
	cout << m10 << endl;
	
	try { Matrix<int> m = { {1, 2, 3}, {4, 6}, {7, 8, 9} }; } // ������ �������� ���������� �.�. ������ ���-�� ��������� � �������
	catch (std::exception& ex) { cerr << ex.what() << endl << endl; }

	try { Matrix<StrangeClass> m(4); } // ������ �������� ���������� �.�. ��������� ����������� ������ ����������
	catch (std::exception& ex) { cerr << ex.what() << endl << endl; }

	try { Matrix<StrangeClass> m = { 11, 22, 33, 44 }; } // ������ �������� ���������� �.�. ����������� � 1 ���������� ��� ���������� ��� �������� 3-�� ��������
	catch (std::exception& ex) { cerr << ex.what() << endl << endl; }

	cout << "-------------------------------------------------------" << endl;
}

void test_assignment() {
	cout << "-----------------------TEST_ASSIGNMENT-----------------------" << endl;
	Matrix<> m_d = { {1.1, 2.1, 3.1}, {4.1, 5.1, 6.1}, {7.1, 8.1, 9.1} };
	cout << m_d << endl;
	Matrix<int> m1 = { 1, 2, 3, 4, 5, 6 };
	cout << m1 << endl;
	Matrix<int> m2; // ������ �������
	cout << m2 << endl;

	m1 = m1; // ��������� �������� �� ����������������

	m2 = m1; // ���������� ������������
	cout << m2 << endl;

	m2 = m_d; // ���������� ������������ ��������� (�.�. ���� ������)
	cout << m2 << endl;

	cout << m1 << endl; // ��� ����� m1 ���
	cout << m2 << endl; // ��� ����� m2 ���
	m2 = std::move(m1); // ������������ ����������� (�.�. ���� ����������)
	cout << m1 << endl; // ������ m1 ��������� m2
	cout << m2 << endl; // � ��� ����� m2 ����

	cout << m_d << endl; // ��� ����� m_d ���
	cout << m2 << endl;  // ��� ����� m2 ���
	m2 = std::move(m_d); // ���������� ����������� ��������� (�.�. ���� ������)
	cout << m_d << endl; // m_d �� ���������
	cout << m2 << endl;  // � ��� ����� m2 ����

	m2 += m_d; // ������ ����, ������� ������� ��� ������������ +=
	cout << m2 << endl;
	m2 -= m_d; // ������ ����, ������� ������� ��� ������������ -=
	cout << m2 << endl;
	m2 *= Matrix<double>{0, 1, 0}; // ������ ����, ������� ������� ��� ������������ ���������
	cout << m2 << endl;
	m2 *= 2.5; // ������ ����, ������� ������� ��� ������������ *=
	cout << m2 << endl; // �� ���������� �.�. *static_cast<int>(1.5)
	m_d *= 0;
	cout << m_d << endl; // ������ ����������

	try { m_d += Matrix<int>{1, 2, 3, 4}; }
	catch (std::exception& ex) { cerr << ex.what() << endl << endl; }

	try { m_d -= Matrix<int>{1, 2, 3, 4}; }
	catch (std::exception& ex) { cerr << ex.what() << endl << endl; }
	cout << "-------------------------------------------------------" << endl;
}

void test_ij() {
	cout << "------------------------TEST_IJ------------------------" << endl;
	try { cout << Matrix<>{}(0, 0) << endl; } // ������
	catch (std::exception& ex) { cerr << ex.what() << endl << endl; }

	try { cout << Matrix<>(5)(0, 1) << endl; } // 1 �������
	catch (std::exception& ex) { cerr << ex.what() << endl << endl; }

	try { cout << Matrix<>(1, 5)(1, 0) << endl;} // 1 ������
	catch (std::exception& ex) { cerr << ex.what() << endl << endl; }

	Matrix<int> m = { {1, 2, 3}, {4, 5, 6} };
	cout << m << endl;
	cout << m(0, 2) << endl;
	m(0, 2) = 7; // ������ 1-�� ������, 3-�� ������� ���� ����� 7
	cout << m(0, 2) << endl;
	cout << m << endl;

	const Matrix<int> c_m = { {1, 2, 3}, {4, 5, 6} };
	cout << c_m << endl;
	cout << c_m(0, 2) << endl;
	//c_m(0, 2) = 7; // �� ������ ���������������� (���� ������ ������ �������� ����������� �������)

	cout << "-------------------------------------------------------" << endl;
}

void test_cout() {
	cout << "-----------------------TEST_COUT-----------------------" << endl;
	Matrix<const char*> m{ {"This", "is", "my"}, {"best", "matrix", "ever"}};
	cout << m << endl;
	Matrix<std::string> m_str = m;
	cout << m_str << endl;
	m_str += Matrix<const char*>{ {"111", "22", "3"}, {"4", "55", "666"} };
	cout << m_str << endl;
	cout << "-------------------------------------------------------" << endl;
}

void test_arithmetic() {
	cout << "--------------------TEST_ARITHMETIC--------------------" << endl;
	Matrix<int> m_i = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	cout << m_i << endl;
	Matrix<double> m_d = { {1.2, 2.1, 3.5}, {4.4, 5.5, 6.1}, {7.5, 8.0, 9.1} };
	cout << m_d << endl;

	cout << "SUM unary:" << endl;
	cout << +m_i << endl;

	cout << "MINUS unary:" << endl;
	cout << -m_i << endl;

	cout << "SUM binary:" << endl;
	cout << m_i + m_d << endl;

	cout << "MINUS binary:" << endl;
	cout << m_i - m_d << endl;

	cout << "MULTIPLY by matrix:" << endl;
	cout << m_i * m_d << endl;

	cout << "MULTIPLY by value (left):" << endl;
	cout << 4 * m_d << endl;
	cout << "MULTIPLY by value (right):" << endl;
	cout << m_i * 1.5 << endl;

	try { Matrix<int>{ {1, 2}, { 4, 5 } } + m_d; }
	catch (std::exception& ex) { cerr << ex.what() << endl; }

	try { Matrix<int>{ {1, 2}, { 4, 5 } } - m_d; }
	catch (std::exception& ex) { cerr << ex.what() << endl; }

	try { Matrix<int>{ {1, 2}, { 4, 5 } } * m_d; }
	catch (std::exception& ex) { cerr << ex.what() << endl; }

	cout << "-------------------------------------------------------" << endl;
}

void test_capacity() {
	cout << "------------------_--TEST_CAPACITY-----------_---------" << endl;
	Matrix<int> m = { {1, 2}, {3 , 4}, {5, 6} };
	cout << m;
	cout << "capacity: " << m.capacity() << endl << endl;

	Matrix<int> m_1 = { {1, 2,   3},{4,   5, 6} };
  	m = m_1; // ������������ ������ �� ��������
	cout << m;
	cout << "capacity: " << m.capacity() << endl << endl;

	Matrix<double> m_2 = { {1, 2}, {3 , 4}};
	m = m_2; // ������������ ������ �� ��������
	cout << m;
	cout << "capacity: " << m.capacity() << endl << endl;

	Matrix<double> m_3 = { {1, 2}, {3 , 4}, {5, 6}, {7 , 8} };
	m = m_3; // ��� ������ �������� ������������ ������
	cout << m;
	cout << "capacity: " << m.capacity() << endl << endl;

	cout << "-------------------------------------------------------" << endl;
}

void test_alloc() {
	cout << "----------------------TEST_ALLOC-----------------------" << endl;
	Matrix<double> matrix1 = { {1, 2}, {4, 5} };
	Matrix<int, Allocator_other<int>> matrix2 = { {1, 2}, {4, 5} };
	cout << matrix1 + matrix2 << endl; // ������ ������� ��� ������� � ������� �����������
	matrix2 = matrix1; // ������ ��������� ������� � ������ ����������
	cout << matrix2 << endl;
	cout << "-------------------------------------------------------" << endl;
}