#pragma once
#include <iostream>
using namespace std;

void func(int a) {
	cout << "func(int)" << endl;
}
void func(double* p) {
	cout << "func(double*)" << endl;
}