#include "Card.h"
#include "pclaf.h"

Card::Card(int xv, int yv, int s, int r)
	: Rect(xv, yv, xv + CardWidth, yv + CardHeight),
	suit(s), rank(r), faceUp(false)
{}

void Card::draw(Application& win)
{
	//draw the outer Rect
	Rect::draw(win);
	// then draw the inner contents
	if (faceUp) {
		// first print out the suit
		if (suit == 1 || suit == 4) win.setTextColor(brightRed);
		win.wout << setpos(upperLeftX + 5, upperLeftY + 5);
		if (suit == 1) win.wout << TEXT("heart");
		else if (suit == 2) win.wout << TEXT("club");
		else if (suit == 3) win.wout << TEXT("spade");
		else if (suit == 4) win.wout << TEXT("diamond");
		// then print out the rank
		win.wout << setpos(upperLeftX + 5, upperLeftY + 20);
		if (rank == 1) win.wout << TEXT("ace");
		else if (rank == 11) win.wout << TEXT("jack");
		else if (rank == 12) win.wout << TEXT("queen");
		else if (rank == 13) win.wout << TEXT("king");
		else win.wout << rank;
		if (suit == 1 || suit == 4)
			win.setTextColor(black);
	}
	else {
		// face down, draw back
		win.wout << setpos(upperLeftX + 30, upperLeftY + 38);
		win.wout << TEXT("Back");
		win.line(upperLeftX, upperLeftY,
			upperLeftX + CardWidth, upperLeftY + CardHeight);
		win.line(upperLeftX + CardWidth, upperLeftY,
			upperLeftX, upperLeftY + CardHeight);
	}
}

void Card::flip()
{
	if (faceUp)
		faceUp = false;
	else
		faceUp = true;
}

bool operator==(const Card& c1, const Card& c2)
{
	if (c1.suit == c2.suit) {
		if (c1.rank == c2.rank) {
			return true;
		}
	}

	return false;
}

std::ostream& operator<<(std::ostream& os, const Card& c)
{
	// ..
}
