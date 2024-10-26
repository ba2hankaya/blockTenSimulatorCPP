#include <vector>
#include "deck.h"
#include <stdlib.h>
#include <chrono>
using namespace std;


using namespace std::chrono;
uint64_t timeSinceEpochMillisec() {
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

card PickARandomCard(vector<card>& deck){
	srand(timeSinceEpochMillisec());
	if(deck.size() == 0){
		return EmptyCard;
	}

	//if(deck.size() == 0){
	//	card x;
	//	x.value = 10;
	//	CardSuit s = Spades; 
	//	x.suit = s;
	//	return x;
	//}
	int index = rand() % deck.size();
	card mycard = deck[index];
	deck.erase(deck.begin()+index);
	return mycard;
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
