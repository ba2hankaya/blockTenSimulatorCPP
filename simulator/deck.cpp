#include <vector>
#include "deck.h"
#include <algorithm>
#include <random>
using namespace std;

void ShuffleDeck(vector<card>& deck){
	random_shuffle(deck.begin(),deck.end());
}

card GetXthCard(const vector<card>& deck, const int& index){
	return index >= deck.size() ? EmptyCard : deck[index];
}

vector<card> CreateDeck(){
	vector<card> deck;
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
			deck.push_back(mycard);
		}
	}
	return deck;
}
