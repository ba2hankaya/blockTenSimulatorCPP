#include <vector>
#include "deck.h"
#include <algorithm>
#include <random>
using namespace std;


Deck::Deck(){
	for(int j = 0; j < 4; ++j){
	//	enum CardSuit temp;
	//	switch(j){
	//		case 0:
	//			temp = Spades;
	//			break;
	//		case 1:
	//			temp = Hearts;
	//			break;
	//		case 2:
	//			temp = Diamonds;
	//			break;
	//		case 3:
	//			temp = Clubs;
	//			break;
	//	}
		for(int i = 1; i <= DECK_SIZE/4; i++){
			card mycard = {static_cast<CardSuit>(j) , i};
			deckarr[i+j*13] = mycard;
		}
	}
}

card Deck::CardAtIndex(const int& index){
	return index >= DECK_SIZE ? EmptyCard : deckarr[index];
}

void Deck::Shuffle(){
	shuffle(&deckarr[0], &deckarr[DECK_SIZE]);
}

card Deck::GetAndRemoveTopCard(){
	card toReturn = index > DECK_SIZE ? EmptyCard : deckarr[index];
	index++;
	return toReturn;
}

