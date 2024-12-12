#include "PenApp.h"

PenApp::PenApp(const TCHAR* apName, int width, int height, int x, int y)
	: Application(apName, width, height, x, y)
{}

void PenApp::mouseDown(int x, int y)
{
	// set location to move to
	newx = x;
	newy = y;

	// pen 속성 변경
	//setPen(Color::blue, LineStyle::dashedLine, 3);

	// then update the screen
	clearAndUpdate();	// -> call paint()
}

// paint 함수 호출 경우
//	(1) clearAndUpdate 함수에 의한 호출
//	(2) 프로그램 실행 초기에 윈도우가 처음 표시될 때 호출
//	(3) 윈도우 크기가 변경되거나 다른 윈도우에 가려졌다가 다시 나타날 때 호출
void PenApp::paint()
{
	// draw a line
	line(oldx, oldy, newx, newy);
	// update old locations
	oldx = newx;
	oldy = newy;
}

// pclaf program entry point
int mainLAF()
{
	PenApp theApp(TEXT("PENS"), 500, 500, 150, 150);
	theApp.run();

	return 0;
}