#include "RectApp.h"
#include "Rect.h"

RectApp::RectApp(const TCHAR* apName, int width, int height, int x, int y)
	: Application(apName, width, height, x, y)
{}

void RectApp::mouseDown(int x, int y)
{
#if defined(MULTI_RECT)
	if (rectCount == 0) {
		theRectPtrs[rectCount] = std::make_shared<Rect>(x, y, x + 70, y + 50);
		++rectCount;
	}
	else {
		if (rectCount < MAX_RECTS) {
			if (theRectPtrs[rectCount - 1]->includes(x, y)) {
				theRectPtrs[rectCount] = std::make_shared<Rect>(x, y, x + 70, y + 50);
				rectCount = rectCount + 1;
			}
		}
	}
#else
	if (theRectPtr != nullptr) {
		if (theRectPtr->includes(x, y)) {
			// move the rectangle
			theRectPtr->moveTo(x, y);
		}
	}
	else {
		// raw pointer
		//theRectPtr = new Rect(x, y, x + 70, y + 50);

		// unique_ptr
		theRectPtr = std::make_unique<Rect>(x, y, x + 70, y + 50);
		//theRectPtr = std::unique_ptr<Rect>(new Rect(x, y, x + 70, y + 50));
		// -> make_unique를 사용하는 것이 객체 생성과 초기화에 최적화됨
	}
#endif

	// then update the screen
	clearAndUpdate();
}

void RectApp::paint()
{
#if defined(MULTI_RECT)
	for (int i = 0; i < rectCount; i++) {
		theRectPtrs[i]->draw(*this);
	}
#else 
	if (this->theRectPtr != nullptr)
		theRectPtr->draw(*this);
#endif
}

#if defined(MULTI_RECT)
void RectApp::mouseRDown(int x, int y)
{
	for (int i = rectCount - 1; i >= 0; i--) {
		if (theRectPtrs[i]->includes(x, y)) {
			int delIdx = i;
			for (int j = delIdx; j < rectCount; j++) {
				theRectPtrs[j] = nullptr;
			}
			rectCount -= (rectCount - delIdx);
			break;
		}
	}

	// then update the screen
	clearAndUpdate();
}
#endif

// pclaf program entry point
int mainLAF()
{
	// 콘솔 출력 추가
	// 콘솔 창 생성
	AllocConsole();
	// 콘솔 출력에 대한 스트림 연결
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);

	RectApp theApp(TEXT("RECTANGLES"), 750, 500, 150, 150);
	theApp.run();

	// raw pointer
	//delete theApp.theRectPtr;
	//theApp.theRectPtr = nullptr;

	return 0;
}