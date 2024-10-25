
#ifndef DECK_H
#define DECK_H

enum CardSuit
{
	Spades,
	Hearts,
	Diamonds,
	Clubs
};

struct card
{
	enum CardSuit suit;
	int value;
};

std::vector<card> CreateDeck();

#endif


