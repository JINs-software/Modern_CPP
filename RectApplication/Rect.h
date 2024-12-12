// RECTANGLE CLASS
#pragma once

/* [선행 선언(forward declaration)]
	* 'pclaf.h'에 정의된 'Application' 클래스에 대한 선행(전방) 선언
	* 현재 헤더 파일에는 Application 클래스가 함수의 파라미터 타입으로만 사용되었기에,
	* pclaf.h를 포함하기 보단, 선행 선언을 통해 컴파일러에 클래스의 존재만을 알리도록 하는 것이다.
	* 실제 컴파일 대상이 되는 Rect.cpp에는 pclaf.h가 포함되어야 한다.
*/
class Application;	// 선행(전방) 선언

class Rect
{
public:
	// constructor
	Rect(int, int, int, int);
	~Rect();

	// operations
	void moveTo(int, int);
	bool includes(int, int);
	virtual void draw(Application&);

	// data fields
	int upperLeftX;
	int upperLeftY;
	int lowerRightX;
	int lowerRightY;
};