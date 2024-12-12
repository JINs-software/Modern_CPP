#pragma once
#include <iostream>
using namespace std;

constexpr size_t getArraySize(int k) {
	return k == 0 ? 10 : k;
}

/* [constexpr]
	* constexpr 지시자로 명시한 변수나 함수는 컴파일 시 그 값을 결정할 수 있다는 것을 컴파일러에 전달하여,
	* 컴파일러가 constexpr로 명시한 코드를 최적화할 수 있게 해준다.
	
 * [constexpr 표현식]
	* 상수 / constexpr 변수 / constexpr 함수로 구성된 식을 의미
	* 컴파일러가 constexpr 표현식의 값을 결정할 수 없으면 컴파일 오류가 발생

	* 참고로 constexpr 함수는 return 문을 한 개만 가질 수 있다.
*/

void Example_ConstExpr() {
	//int num = 10;
	//int myArray[1 + getArraySize(num)];	// <- comile error...

	//constexpr int num = 10;
	//int myArray[1 + getArraySize(num)];	// <- OK

	// getArraySize 함수는 상수가 요구되는 곳에 사용할 수 있는 함수!
	// getArraySize 함수에 전달되는 인수는 0과 같은 상수를 전달하여 constexpr 표현식을 갖추었다.
	int myArray[1 + getArraySize(0)];	
	int count = 0;
	for (size_t i = 0; i < 1 + getArraySize(0); i++) {
		myArray[i] = i;
		count += 1;
	}

	cout << "Array Size: " << count << endl;
}

/* [static_assert]
	* constexpr 표현식이 컴파일 시 예상한 값을 갖는지 검사하는 용도의 함수
*/

void Example_Static_Assert() {
	constexpr int x = 123;
	static_assert(x == 123, "the constexpr value is not 456");

	//static_assert(x == 456, "the constexpr value is not 456"); 
	// -> 컴파일 오류 발생
}