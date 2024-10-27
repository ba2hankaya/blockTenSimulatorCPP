#include <vector>
#include "deck.h"
#include <algorithm>
#include <random>
using namespace std;


Deck::Deck(){
	for(int j = 0; j < 4; ++j){
		enum CardSuit temp;
		switch(j){
			case 0:
				temp = Spades;
				break;
			case 1:
				temp = Hearts;
				break;
			case 2:
				temp = Diamonds;
				break;
			case 3:
				temp = Clubs;
				break;
		}
		for(int i = 1; i <= 13; i++){
			card mycard = {temp , i};
			card_vec.push_back(mycard);
		}
	}
}

card Deck::CardAtIndex(const int& index){
	return index >= card_vec.size() ? EmptyCard : card_vec[index];
}

void Deck::Shuffle(){
	random_shuffle(card_vec.begin(), card_vec.end());
}

card Deck::GetAndRemoveTopCard(){
	card toReturn = index > card_vec.size() ? EmptyCard : card_vec[index];
	index++;
	return toReturn;
}

