#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <thread>
#include <mutex>
#define table_length 3
using namespace std;

enum CardSuit{
        Spades,
        Hearts,
        Diamonds,
        Clubs
};

struct card{
        enum CardSuit suit;
        int value;
};

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

card PickARandomCard(vector<card>& deck){
		if(deck.size() == 0){
			card x;
			x.value = 10;
			CardSuit s = Spades; 
			x.suit = s;
			return x;
		}
        int index = rand() % deck.size();
        card mycard = deck[index];
        deck.erase(deck.begin()+index);
        return mycard;
}

vector<card> GenTable(vector<card>& deck){
        vector<card> table(table_length*table_length);
        for(int j = 0; j < table_length*table_length; ++j){
                table[j] = PickARandomCard(deck);
        }
        return table;
}

void printTable(const vector<card>& table){
    for(card mycard : table){
        cout << mycard.value << " " << to_string(mycard.suit) << endl;
    }
    cout << "--------------------------------------" << endl;
}

int numberOfMoves(){
        vector<card> deck = CreateDeck();
        vector<card> table = GenTable(deck);
        //printTable(table);
		int count = 0;
		int x = -1;
		while(x != count){
			x = count;
			for(int i = 0; i < table.size()-1; i++){
				if(table[i].value == 10){
					continue;
				}
				for(int j = i+1; j < table.size(); j++){
					if(table[i].value == table[j].value){
						count++;
						table[i] = PickARandomCard(deck);
						table[j] = PickARandomCard(deck);
						goto end;
					}
				}
			}
			end:
		}
        return count;
}

#include <chrono>
using namespace std::chrono;
uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void FillMap(map<int, int>& mp, int x){
	while(x>0){
	int res = numberOfMoves();
		if(mp.find(res) == mp.end()){
			mp[res] = 1;
		}else{
			mp[res]++;
		}
		x--;
	}
}

int main(int argc, char* argv[]){

    srand(timeSinceEpochMillisec());
	cout << "running " << stoi(argv[1]) << " simulations..." << endl;
	int x = stoi(argv[1]);
	vector<thread> th_list;
	mutex map_mutex;
	vector<map<int ,int>> thread_maps(4);
	map<int , int> mp;
	if(x>1000){
		for(int i = 0; i < 4; i++){
			th_list.push_back(thread(FillMap, ref(thread_maps[i]), x/4));
		}
		for(auto& t : th_list){
			t.join();
		}
	}else{
		FillMap(mp, x);
	}

	for (const auto& local_map : thread_maps) {
        std::lock_guard<std::mutex> lock(map_mutex);
        mp.insert(local_map.begin(), local_map.end());
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
