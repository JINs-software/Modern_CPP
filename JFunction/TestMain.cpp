#include <iostream>
#include "JFunction.h"

// Lambda object
JFunction<double(int, int)> lambda;
// Function object
JFunction<double(int, int)> func;


double Divide(int a, int b) {
	if (b != 0) {
		return (double)a / b;
	}
	return 0;
}

void Func() {
	std::cout << "(in Func), lambda(1, 2) = " << lambda(1, 2) << std::endl;
}

int main() {
	double vx = 0.3;
	double rx = 0;
	
	// 람다 저장
	lambda = [vx, &rx](int a, int b)->double {
		return vx + rx + a + b;
		};

	// 일반 함수 저장
	func = &Divide;

	double ret1 = lambda(1, 2);
	double ret2 = func(1, 2);
	std::cout << "ret1: " << ret1 << ", ret2: " << ret2 << std::endl;
	// -> ret1: 3.3, ret2: 0.5

	rx = 1;
	ret1 = lambda(1, 2);
	std::cout << "ret1: " << ret1 << std::endl;		// -> ret1: 4.3

	rx = 2;
	ret1 = lambda(1, 2);
	std::cout << "ret1: " << ret1 << std::endl;		// -> ret1: 5.3

	Func();
	rx = 3;
	Func();
	rx = 4;
	Func();
}