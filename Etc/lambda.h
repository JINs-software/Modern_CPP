#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace  std;

/* [람다(lambda)]
	* 컴파일러는 '람다 표현식'으로부터 함수 객체를 생성
	* 보통 람다 표현식과 함수 객체를 구분하지 않고, 람다 또는 람다 함수라고 혼용하여 언급
	
	* 람다 함수는 자기가 속한 스코프 내 지역 변수들을 파라미터로 전달받지 않고도 함수 내에서 사용 가능
*/


class IsOdd {
public:
	bool operator()(int i) {
		return ((i % 2) == 1);
	}
};
void Example_Labmda_with_Algorithm() {
	// find_if 알고리즘 함수의 '조건자'로 함수 객체/람다 함수를 전달
	vector<int> intVector;
	intVector.push_back(10);
	intVector.push_back(32);
	intVector.push_back(21);
	intVector.push_back(26);
	
	// 조건자: 함수 객체(functor)
	IsOdd isOdd;
	auto it = find_if(intVector.begin(), intVector.end(), isOdd);
	cout << "첫 번째 홀수(조건자: 함수 객체): " << *it << endl;

	// 조건자: 람다
	auto it2 = find_if(intVector.begin(), intVector.end(), 
		[](int i) -> bool {
			return ((i % 2) == 1);
		});
	cout << "첫 번째 홀수(조건자: 람다): " << *it2 << endl;
}


/* [람다 캡쳐(lambda capture)]
	* 함수 객체는 객체이므로 상태 정보를 저장하는 멤버 변수를 가질 수 있다.
	* 람다 또한 컴파일러에 의해 함수 객체로 구현되므로 람다도 상태 정보를 가질 수 있다.
	
	* []: '캡쳐 클로저(capture closure)'
	* [] 내의 캡쳐 리스트로 주변 변수들을 가져와 상태로 저장한다.
	
	* (축약 표현, 권장되지는 않음)
	* [=]: 스코프 내 모든 지역 변수의 현재 값을 캡쳐
	* [&]: 스코프 내 모든 지역 변수의 레퍼런스를 캡쳐
*/
void Example_Lambda_Capture() {
	// (1) capture by value
	int intVal = 100;
	auto lambdaFunc = [intVal]() {
		cout << "copy of intVal: " << intVal << endl;
		};
	// 람다가 생성될 때 지역 변수 값을 캡쳐
	// lambdaFunc는 이미 intVal(100)을 상태로 캡쳐한 상태,
	// 따라서 아래 for문에서 intVal을 증분하더라도 내부 상태에서는 변화가 없음
	for (int i = 0; i < 3; i++) {
		++intVal;
		lambdaFunc();
	}


	// (2) capture by reference
	intVal = 100;
	auto lambdaFunc2 = [&intVal]() {
		cout << "reference of intVal: " << intVal << endl;
		};
	// lambdaFunc2는 지역변수 intVal의 레퍼런스를 캡쳐
	for (int i = 0; i < 3; i++) {
		++intVal;
		lambdaFunc2();
	}


	intVal = 100;
	auto lambdaFunc3 = [&intVal]() {
		intVal += 50;
		};
	// lambdaFunc3는 지역변수 intVal의 레퍼런스를 캡쳐
	lambdaFunc3();
	cout << "intVal: " << intVal << endl;



	// [mutable 키워드]
	// 람다로부터 생성한 함수 객체의 함수 호출 연산자는 const 멤버 함수로 정의됨
	// 따라서 변수를 레퍼런스로 캡쳐하지 않는 한, 캡쳐한 변수의 값을 변경할 수 없음
	// 만약 값을 변경하고 싶다면 'mutable' 키워드 사용
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