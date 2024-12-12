#include "CardApp.h"

CardApp::CardApp(const TCHAR* apName)
	: Application(apName)
{}

CardApp::CardApp(const TCHAR* apName, int width, int height, int x, int y)
	: Application(apName, width, height, x, y)
{}

void CardApp::mouseDown(int x, int y)
{
	if (b.includes(x, y))
		b.flip();
	
	if (c->includes(x, y)) {
		// [static_pointer_cast]
		// - 스마트 포인터 타입 변환: static_pointer_cast
		// - C 포인터(raw pointer) 타입 변환: static_cast
		
		// typedef std::shared_ptr<Card> CardPtr;
		CardPtr k = std::static_pointer_cast<Card>(c);
		k->flip();
	}
	
	clearAndUpdate();
}

void CardApp::paint()
{
	a.draw(*this);
	b.draw(*this);
	
	// typedef std::shared_ptr<Card> CardPtr;
	CardPtr k = std::static_pointer_cast<Card>(c);
	k->draw(*this);
	// == c->draw(*this);
	
}

// pclaf program entry point
int mainLAF()
{
	CardApp theApp(TEXT("CARDS"));
	theApp.run();

	return 0;
}