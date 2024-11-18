#include <vector>
#include "deck.h"
#include <algorithm>
#include <random>
using namespace std;


Deck::Deck(){
	for(int j = 1; j <= 4; ++j){
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
		}
		for(int i = 1; i <= DECK_SIZE/4; i++){
			card mycard = {j , i};
			deckarr[i+(j-1)*13](mycard);
		}
	}
}

card Deck::CardAtIndex(const int& index){
	return index >= DECK_SIZE ? EmptyCard : deckarr[index];
}

void Deck::Shuffle(){
	random_shuffle(&deckarr[0], &deckarr[DECK_SIZE]);
}

card Deck::GetAndRemoveTopCard(){
	card toReturn = index > DECK_SIZE ? EmptyCard : deckarr[index];
	index++;
	return toReturn;
}

