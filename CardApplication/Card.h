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
	// ���� ��� ��� (��� ī�� ��ü�� ��� ����μ� �޸𸮸� ���� x)
	static const int CardWidth = 75;
	static const int CardHeight = 100;

	static int getCardWidth() {
		return CardWidth;
	}

	// friend ����
	// ������ ������ �Լ��� friend ������ �شٴ� �ǹ�
	friend bool operator==(const Card&, const Card&);
	friend std::ostream& operator<<(std::ostream&, const Card&);

	// data fields
	int suit;
	int rank;
	bool faceUp;
};

// extern: �ܺ� ����
// �ٸ� ���Ͽ� ���ǵ� ���� ����/�Լ��� ������ �� �ֵ��� ��
// (�Լ� ����(����)�� cpp ���Ͽ���)
extern bool operator==(const Card&, const Card&);
extern std::ostream& operator<<(std::ostream&, const Card&);

typedef std::shared_ptr<Card> CardPtr;