//====================================================================
// �ǽ� ����
// ���콺 Ŭ������ ���� �� ������, �� 70, ���� 50�� û�� �簢���� �׸�
// ������ �簢�� ������ Ŭ���ϸ� �� ������ �簢���� �̵�
//====================================================================
#pragma once
#include "pclaf.h"
#include <memory>
#include <array>

/* [����(����) ���� ���ǻ���]
	* RectApp Ŭ���� ����� �����ϴ� 'theRectPtr'�� Ÿ���� Rect�� ������ ���̴�.
	* �����Ϸ��� Rect ��ü�� �����ϴ� �޸� ũ�⸦ �� �ʿ䰡 ����. �������̱� �����̴�.
	* �׷��� 'theRectObj'�� ����� ���´ٸ� ������ ������ �߻��Ѵ�.
	* �����Ϸ��� Rect ��ü�� �޸� ũ�⸦ �˾ƾ� �ϴµ�, Rect.h�� �������� �ʱ� �����̴�.
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