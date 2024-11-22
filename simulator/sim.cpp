#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include "deck.h"
#include <chrono>
#define table_length 3
#define THREADNUM 2
using namespace std;


vector<card> GenTable(Deck& deck){
	vector<card> table(table_length*table_length);
	for(int i = 0;i < table_length*table_length;i++){
		table[i] = deck.GetAndRemoveTopCard();
	}
	return table;
}

void printTable(const vector<card>& table){
    for(card mycard : table){
        cout << mycard.value << " " << to_string(mycard.suit) << endl;
    }
    cout << "--------------------------------------" << endl;
}

int numberOfMoves(Deck& deck){
	int currentIndex = 0;
	vector<card> table = GenTable(deck);
//	printTable(table);
	int count = 0;
	int x = -1;
	while(x != count){
		x = count;
		for(int i = 0; i < table.size()-1; i++){
			if(table[i].value == 10){
				continue;
			}
			if(table[i].value == -1){
				continue;
			}
			for(int j = i+1; j < table.size(); j++){
				if(table[j].value == -1){
					continue;
				}
				if(table[i].value + table[j].value == 10 || (table[i].value > 10 && table[i].value == table[j].value)){
					count++;
					table[i] = deck.GetAndRemoveTopCard();
					table[j] = deck.GetAndRemoveTopCard();
					//printTable(table);
					goto end;
				}
			}
		}
		end:
	}
	return count;
}

uint64_t ms(){
	using namespace std::chrono;
	return (duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count());
}

void FillMap(map<int, int>& mp, int x){
	srand(ms());
	while(x>0){
		Deck deck;
		deck.Shuffle();
		int res = numberOfMoves(deck);
		mp[res]++;
		x--;
	}
}

map<int , int> spawnThreads(const int& n, const int& numOfAttempts){
	map<int , int> ret;
	vector<map<int , int>> localmaps(n);
	vector<thread> threads(n);
	for(int i = 0; i < n; i++){
		threads[i] = thread(FillMap, ref(localmaps[i]), numOfAttempts/n);
	}
	for(auto& t : threads){
		t.join();
	}
	for(int i = 0; i < n;i++){
		for(auto& line : localmaps[i]){
			ret[line.first] += line.second;
		}
	}
	return ret;
}

int main(int argc, char* argv[]){
	cout << "running " << stoi(argv[1]) << " simulations..." << endl;
	int x = stoi(argv[1]);
	map<int , int> mp;
	if(x>1000){
		mp = spawnThreads(THREADNUM, x);
	}
	else{
		FillMap(mp, x);
	}
    for(auto& line : mp){
		cout << line.first << " : " << line.second << endl;
	}
    cout << "end of report";
    return 0;
}
