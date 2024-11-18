#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include "deck.h"
#define table_length 3
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
				if(table[i].value == table[j].value){
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


void FillMap(map<int, int>& mp, int x){
	while(x>0){
		Deck deck;
		deck.Shuffle();
		int res = numberOfMoves(deck);
		mp[res]++;
		x--;
	}
}

int main(int argc, char* argv[]){
	cout << "running " << stoi(argv[1]) << " simulations..." << endl;
	int x = stoi(argv[1]);
	vector<thread> th_list;
	vector<map<int ,int>> thread_maps(4);
	map<int , int> mp;
	if(x>1000){
		for(int i = 0; i < 4; i++){
			th_list.emplace_back(thread(FillMap, ref(thread_maps[i]), x/4));
		}
		for(auto& t : th_list){
			t.join();
		}
	}else{
		FillMap(mp, x);
	}

	for (const auto& local_map : thread_maps) {
 	       
		for(auto& line : local_map){
			mp[line.first] += line.second;
		}
    }
    for(auto& line : mp){
		cout << line.first << " : " << line.second << endl;
	}
    cout << "end of report";
    return 0;
}
