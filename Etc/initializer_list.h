#pragma once

#include <iostream>
#include <initializer_list>

using namespace std;

/* [초기화 리스트(initialization_list)]
	* 파라미터의 갯수가 가변적인 함수를 작성할 때 편리하게 이용할 수 있는 기능이다.
	* 템플릿 클래스인 initialization_list<T>를 파라미터로 선언하고, '{..}' 형태의 인수를 전달한다.
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