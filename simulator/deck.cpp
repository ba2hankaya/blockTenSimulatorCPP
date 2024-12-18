#include <vector>
#include "deck.h"
#include <algorithm>
#include <random>
using namespace std;


Deck::Deck(){
	for(int j = 0; j < 4; ++j){
		for(int i = 0; i < DECK_SIZE/4; i++){
			card mycard = {static_cast<CardSuit>(j) , i+1};
			deckarr[i+j*13] = mycard;
		}
	}
	rng.seed(seed);
}

card Deck::CardAtIndex(const int& index){
	return index >= DECK_SIZE ? EmptyCard : deckarr[index];
}

void Deck::Shuffle(){
	shuffle(&deckarr[0], &deckarr[DECK_SIZE], rng);
}

card Deck::GetAndRemoveTopCard(){
	card toReturn = index >= DECK_SIZE ? EmptyCard : deckarr[index];
	index++;
	return toReturn;
}

void Deck::SeedRng(const uint32_t& seed){rng.seed(seed);}

void Deck::ResetToLast(){index = 0;} 
