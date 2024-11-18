
#ifndef DECK_H
#define DECK_H

const int DECK_SIZE = 52;

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

class Deck{
	private:
		card[DECK_SIZE] deckarr;
		//std::vector<card> card_vec;
		int index = 0;
	public:
		Deck();
		card GetAndRemoveTopCard();
		void Shuffle();
		card CardAtIndex(const int& index);
};

const card EmptyCard = {Empty,-1};
#endif


