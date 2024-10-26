#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include <mutex>
#include "deck.h"
#define table_length 3
using namespace std;


vector<card> GenTable(vector<card>& deck, int& index){
	vector<card> table(table_length*table_length);
	int j = 0;
	while(j < table_length*table_length){
		table[j] = GetXthCard(deck, j);
		j++;
	}
	index = j;
	return table;
}

void printTable(const vector<card>& table){
    for(card mycard : table){
        cout << mycard.value << " " << to_string(mycard.suit) << endl;
    }
    cout << "--------------------------------------" << endl;
}

int numberOfMoves(vector<card>& deck){
	int currentIndex = 0;
	vector<card> table = GenTable(deck, currentIndex);
	//printTable(table);
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
					table[i] = GetXthCard(deck, currentIndex++);
					table[j] = GetXthCard(deck, currentIndex++);
					goto end;
				}
			}
		}
		end:
	}
	return count;
}


void FillMap(map<int, int>& mp, int x){
	
	vector<card> deck = CreateDeck();
	while(x>0){

		ShuffleDeck(deck);
		int res = numberOfMoves(deck);
		if(mp.find(res) == mp.end()){
			mp[res] = 1;
		}else{
			mp[res]++;
		}
		x--;
	}
}

int main(int argc, char* argv[]){
	cout << "running " << stoi(argv[1]) << " simulations..." << endl;
	int x = stoi(argv[1]);
	vector<thread> th_list;
	mutex map_mutex;
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

    //std::lock_guard<std::mutex> lock(map_mutex);
	for (const auto& local_map : thread_maps) {
 	       
		for(auto& line : local_map){
			mp[line.first] += line.second;
		}
	//	mp.insert(local_map.begin(), local_map.end());
    }
	//FillMap(mp,x);
	//while(x > 0){
	//	int res = numberOfMoves();
		//cout << (100 - x) << " th run";
	//	if(mp.find(res) == mp.end()){
	//		mp[res] = 1;
	//	}else{
	//		mp[res]++;
	//	}
		//cout << "result of run : " << res << endl; 
	//	x--;
	//}
    for(auto& line : mp){
		cout << line.first << " : " << line.second << endl;
	}
    cout << "end of report";
    return 0;
}
