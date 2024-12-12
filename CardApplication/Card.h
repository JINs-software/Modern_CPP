// CARD CLASS
#pragma once
#include "Rect.h"
#include <memory>

class Card : public Rect
{
public:
	// constructor
	Card(int, int, int, int);

	// operations
	virtual void draw(Application&) override;
	void flip();

	// static data fields
	// 정적 멤버 상수 (모든 카드 객체에 상수 멤버로서 메모리를 낭비 x)
	static const int CardWidth = 75;
	static const int CardHeight = 100;

	static int getCardWidth() {
		return CardWidth;
	}

	// friend 선언
	// 전역의 연산자 함수를 friend 권한을 준다는 의미
	friend bool operator==(const Card&, const Card&);
	friend std::ostream& operator<<(std::ostream&, const Card&);

	// data fields
	int suit;
	int rank;
	bool faceUp;
};

// extern: 외부 선언
// 다른 파일에 정의된 전역 변수/함수를 참조할 수 있도록 함
// (함수 정의(구현)은 cpp 파일에서)
extern bool operator==(const Card&, const Card&);
extern std::ostream& operator<<(std::ostream&, const Card&);

typedef std::shared_ptr<Card> CardPtr;