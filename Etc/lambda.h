#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace  std;

/* [����(lambda)]
	* �����Ϸ��� '���� ǥ����'���κ��� �Լ� ��ü�� ����
	* ���� ���� ǥ���İ� �Լ� ��ü�� �������� �ʰ�, ���� �Ǵ� ���� �Լ���� ȥ���Ͽ� ���
	
	* ���� �Լ��� �ڱⰡ ���� ������ �� ���� �������� �Ķ���ͷ� ���޹��� �ʰ� �Լ� ������ ��� ����
*/


class IsOdd {
public:
	bool operator()(int i) {
		return ((i % 2) == 1);
	}
};
void Example_Labmda_with_Algorithm() {
	// find_if �˰��� �Լ��� '������'�� �Լ� ��ü/���� �Լ��� ����
	vector<int> intVector;
	intVector.push_back(10);
	intVector.push_back(32);
	intVector.push_back(21);
	intVector.push_back(26);
	
	// ������: �Լ� ��ü(functor)
	IsOdd isOdd;
	auto it = find_if(intVector.begin(), intVector.end(), isOdd);
	cout << "ù ��° Ȧ��(������: �Լ� ��ü): " << *it << endl;

	// ������: ����
	auto it2 = find_if(intVector.begin(), intVector.end(), 
		[](int i) -> bool {
			return ((i % 2) == 1);
		});
	cout << "ù ��° Ȧ��(������: ����): " << *it2 << endl;
}


/* [���� ĸ��(lambda capture)]
	* �Լ� ��ü�� ��ü�̹Ƿ� ���� ������ �����ϴ� ��� ������ ���� �� �ִ�.
	* ���� ���� �����Ϸ��� ���� �Լ� ��ü�� �����ǹǷ� ���ٵ� ���� ������ ���� �� �ִ�.
	
	* []: 'ĸ�� Ŭ����(capture closure)'
	* [] ���� ĸ�� ����Ʈ�� �ֺ� �������� ������ ���·� �����Ѵ�.
	
	* (��� ǥ��, ��������� ����)
	* [=]: ������ �� ��� ���� ������ ���� ���� ĸ��
	* [&]: ������ �� ��� ���� ������ ���۷����� ĸ��
*/
void Example_Lambda_Capture() {
	// (1) capture by value
	int intVal = 100;
	auto lambdaFunc = [intVal]() {
		cout << "copy of intVal: " << intVal << endl;
		};
	// ���ٰ� ������ �� ���� ���� ���� ĸ��
	// lambdaFunc�� �̹� intVal(100)�� ���·� ĸ���� ����,
	// ���� �Ʒ� for������ intVal�� �����ϴ��� ���� ���¿����� ��ȭ�� ����
	for (int i = 0; i < 3; i++) {
		++intVal;
		lambdaFunc();
	}


	// (2) capture by reference
	intVal = 100;
	auto lambdaFunc2 = [&intVal]() {
		cout << "reference of intVal: " << intVal << endl;
		};
	// lambdaFunc2�� �������� intVal�� ���۷����� ĸ��
	for (int i = 0; i < 3; i++) {
		++intVal;
		lambdaFunc2();
	}


	intVal = 100;
	auto lambdaFunc3 = [&intVal]() {
		intVal += 50;
		};
	// lambdaFunc3�� �������� intVal�� ���۷����� ĸ��
	lambdaFunc3();
	cout << "intVal: " << intVal << endl;



	// [mutable Ű����]
	// ���ٷκ��� ������ �Լ� ��ü�� �Լ� ȣ�� �����ڴ� const ��� �Լ��� ���ǵ�
	// ���� ������ ���۷����� ĸ������ �ʴ� ��, ĸ���� ������ ���� ������ �� ����
	// ���� ���� �����ϰ� �ʹٸ� 'mutable' Ű���� ���
	intVal = 100;
	auto lambdaFunc4 = [intVal]() mutable {
		cout << "lambda adds 10 to intVal(copy of value)" << endl;
		intVal += 10;
		};
	lambdaFunc4();
}

//void Example_Lambda_Generalized_Capture();

//void Example_Lambda_Template();

//void Example_Labmda_Constexpr();