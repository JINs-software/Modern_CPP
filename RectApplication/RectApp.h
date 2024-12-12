//====================================================================
// 실습 과제
// 마우스 클릭점을 왼쪽 위 꼭짓점, 폭 70, 높이 50인 청색 사각형을 그림
// 생성된 사각형 내에서 클릭하면 그 점으로 사각형이 이동
//====================================================================
#pragma once
#include "pclaf.h"
#include <memory>
#include <array>

/* [선행(전방) 선언 주의사항]
	* RectApp 클래스 멤버로 존재하는 'theRectPtr'의 타입은 Rect의 포인터 형이다.
	* 컴파일러는 Rect 객체가 차지하는 메모리 크기를 알 필요가 없다. 포인터이기 때문이다.
	* 그러나 'theRectObj'를 멤버로 갖는다면 컴파일 에러가 발생한다.
	* 컴파일러가 Rect 객체의 메모리 크기를 알아야 하는데, Rect.h를 포함하지 않기 때문이다.
*/
class Rect;
#define MULTI_RECT
#if defined(MULTI_RECT)
const auto MAX_RECTS = 20;
#endif

// Customized Application
class RectApp : public Application
{
public:
	RectApp(const TCHAR*, int, int, int, int);
	void mouseDown(int, int);
	void paint();

	// data field
	//Rect theRectObj;		// compile error..

#if defined(MULTI_RECT)
	void mouseRDown(int, int);

	std::array<std::shared_ptr<Rect>, MAX_RECTS> theRectPtrs;
	int rectCount;
#else
	// raw pointer
	//Rect theRectObj;		// compile error..
	//Rect* theRectPtr = nullptr;

	// unique_ptr
	std::unique_ptr<Rect> theRectPtr;
#endif

};