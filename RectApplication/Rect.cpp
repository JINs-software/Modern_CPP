#include "Rect.h"
#include "pclaf.h"
#include <iostream>

Rect::Rect(int a, int b, int c, int d)
	: upperLeftX(a), upperLeftY(b),
	lowerRightX(c), lowerRightY(d)
{
	std::cout << "Rect's Constructor!" << std::endl;
}
Rect::~Rect() {
	std::cout << "Rect's Destructor!" << std::endl;
}

void Rect::moveTo(int x, int y)
{
	int width = lowerRightX - upperLeftX;
	int height = lowerRightY - upperLeftY;
	upperLeftX = x;
	upperLeftY = y;
	lowerRightX = x + width;
	lowerRightY = y + height;
}

void Rect::draw(Application& theWindow)
{
	// first make sure the pen is correct
	theWindow.setPen(blue, solidLine, 1);
	// then draw the rectangle
	int width = lowerRightX - upperLeftX;
	int height = lowerRightY - upperLeftY;
	theWindow.rectangle(upperLeftX, upperLeftY, width, height);
}

bool Rect::includes(int x, int y)
{
	if ((upperLeftX < x) && (lowerRightX > x))
		if ((upperLeftY < y) && (lowerRightY > y))
			return true;
	return false;
}