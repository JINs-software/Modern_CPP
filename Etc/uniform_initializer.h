#pragma once
#include <vector>
#include <iostream>
using namespace std;

class CRect {
public:
	int lx, rx, dy, uy;

	CRect(int x1, int y1, int x2, int y2) 
	{
		lx = x1; 
		rx = x2;
		dy = y1;
		uy = y2;
		cout << "CRect's Constructor" << endl;
	}

	CRect(const CRect& other) {
		lx = other.lx;
		rx = other.rx;
		dy = other.dy;
		uy = other.uy;
		cout << "CRect's Copy Constructor" << endl;
	}

	CRect(CRect&& other) {
		lx = other.lx;
		rx = other.rx;
		dy = other.dy;
		uy = other.uy;
		cout << "CRect's Move Constructor" << endl;
	}
};

void Example_Uniform_Initializer() {
	vector<CRect> v1{ CRect(1, 2, 3, 4), CRect(10, 11, 12, 13) };	
	//CRect's Constructor
	//CRect's Constructor
	//CRect's Copy Constructor
	//CRect's Copy Constructor
	
	vector<CRect> v2{ {1, 2, 3, 4}, {10, 11, 12, 13} };
	//CRect's Constructor
	//CRect's Constructor
	//CRect's Copy Constructor
	//CRect's Copy Constructor
}