
#ifndef DECK_H
#define DECK_H

enum CardSuit
{
	Spades,
	Hearts,
	Diamonds,
	Clubs,
	Empty
};

struct card
{
	enum CardSuit suit;
	int value;
};

const card EmptyCard = {Empty,-1};

std::vector<card> CreateDeck();
card GetTheXthCard(const std::vector<card>& deck, const int& index);
#endif


