#pragma once
#include <iostream>
using namespace std;

constexpr size_t getArraySize(int k) {
	return k == 0 ? 10 : k;
}

/* [constexpr]
	* constexpr �����ڷ� ����� ������ �Լ��� ������ �� �� ���� ������ �� �ִٴ� ���� �����Ϸ��� �����Ͽ�,
	* �����Ϸ��� constexpr�� ����� �ڵ带 ����ȭ�� �� �ְ� ���ش�.
	
 * [constexpr ǥ����]
	* ��� / constexpr ���� / constexpr �Լ��� ������ ���� �ǹ�
	* �����Ϸ��� constexpr ǥ������ ���� ������ �� ������ ������ ������ �߻�

	* ����� constexpr �Լ��� return ���� �� ���� ���� �� �ִ�.
*/

void Example_ConstExpr() {
	//int num = 10;
	//int myArray[1 + getArraySize(num)];	// <- comile error...

	//constexpr int num = 10;
	//int myArray[1 + getArraySize(num)];	// <- OK

	// getArraySize �Լ��� ����� �䱸�Ǵ� ���� ����� �� �ִ� �Լ�!
	// getArraySize �Լ��� ���޵Ǵ� �μ��� 0�� ���� ����� �����Ͽ� constexpr ǥ������ ���߾���.
	int myArray[1 + getArraySize(0)];	
	int count = 0;
	for (size_t i = 0; i < 1 + getArraySize(0); i++) {
		myArray[i] = i;
		count += 1;
	}

	cout << "Array Size: " << count << endl;
}

/* [static_assert]
	* constexpr ǥ������ ������ �� ������ ���� ������ �˻��ϴ� �뵵�� �Լ�
*/

void Example_Static_Assert() {
	constexpr int x = 123;
	static_assert(x == 123, "the constexpr value is not 456");

	//static_assert(x == 456, "the constexpr value is not 456"); 
	// -> ������ ���� �߻�
}