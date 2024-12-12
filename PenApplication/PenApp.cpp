#include "PenApp.h"

PenApp::PenApp(const TCHAR* apName, int width, int height, int x, int y)
	: Application(apName, width, height, x, y)
{}

void PenApp::mouseDown(int x, int y)
{
	// set location to move to
	newx = x;
	newy = y;

	// pen �Ӽ� ����
	//setPen(Color::blue, LineStyle::dashedLine, 3);

	// then update the screen
	clearAndUpdate();	// -> call paint()
}

// paint �Լ� ȣ�� ���
//	(1) clearAndUpdate �Լ��� ���� ȣ��
//	(2) ���α׷� ���� �ʱ⿡ �����찡 ó�� ǥ�õ� �� ȣ��
//	(3) ������ ũ�Ⱑ ����ǰų� �ٸ� �����쿡 �������ٰ� �ٽ� ��Ÿ�� �� ȣ��
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