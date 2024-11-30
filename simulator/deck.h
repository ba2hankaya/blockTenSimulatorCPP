
#ifndef DECK_H
#define DECK_H

#include <random>
#include <chrono>
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
		card deckarr[DECK_SIZE];
		int index = 0;
		uint32_t seed = 0;
		std::mt19937 rng;
	public:
		Deck();
		card GetAndRemoveTopCard(); // return top card and increment index by 1
		void SeedRng(const uint32_t& seed); // seed = 0 by default, provide seed for rng
		void Shuffle(); // shuffle the deck using rng
		card CardAtIndex(const int& index);
		void ResetToLast(); // resets the deck not to the default but to how it was last  (set index to 0)
};

const card EmptyCard = {Empty,-1};
#endif


