#pragma once

#include <iostream>
#include <initializer_list>

using namespace std;

/* [�ʱ�ȭ ����Ʈ(initialization_list)]
	* �Ķ������ ������ �������� �Լ��� �ۼ��� �� ���ϰ� �̿��� �� �ִ� ����̴�.
	* ���ø� Ŭ������ initialization_list<T>�� �Ķ���ͷ� �����ϰ�, '{..}' ������ �μ��� �����Ѵ�.
*/

void makeSum(initializer_list<int> lst) {
	int total = 0;
	cout << "initializer_list<int>: ";
	for (auto it = lst.begin(); it != lst.end(); ++it) {
		cout << *it << " ";
		total += *it;
	}
	cout << endl << "total: " << total << endl;
}

void Example_Initialization_List() {
	makeSum({ 1, 2, 3, 4, 5 });
	makeSum({ 1, 10, 100, 1000, 10000 });
}