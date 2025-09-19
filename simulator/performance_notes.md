for x = 10,000,000 

1 thread 
real    0m22.565s
user    0m22.511s
sys     0m0.004s


2 threads 
real    0m11.217s
user    0m22.371s
sys     0m0.014s


4 threads
real    0m5.515s
user    0m21.961s
sys     0m0.010s


8 threads
real    0m2.863s
user    0m22.634s
sys     0m0.010s


16 threads
real    0m2.352s
user    0m36.847s
sys     0m0.013s


cpu = AMD 7800x3D 16 core

Note: When I changed the algorithm for counting moves to use a hash_map and stack instead to lower the time complexity, because the table length is really small and the algorithm is ran millions of times, operation overhead caused the algorithm to perform slower than the bruce-force method. However the performance was much better compared to the brute force method with higher table length and deck size as expected.

The better time complexity but slower performance algorithm:

```

int correspondingValue(const int value)
{
    if (value == 10 || value == -1) {
        throw std::invalid_argument("received value 10 or -1");
    }
    if (value > 10) {
        return value;
    }
    return 10 - value;
}

int numberOfMoves(Deck& deck)
{
    card table[table_length * table_length];
    unordered_map<int, vector<int>> mp;
    queue<int> tryRemoveIndex;
    int count = 0;
    for (int i = 0; i < table_length * table_length; i++) {
        card c = deck.GetAndRemoveTopCard();
        table[i] = c;
        tryRemoveIndex.push(i);
    }

    while (!tryRemoveIndex.empty()) {
        int i = tryRemoveIndex.front();
        tryRemoveIndex.pop();
        card tryRem = table[i];

        if (tryRem.value == -1 || tryRem.value == 10) {
            continue;
        }

        int corVal = correspondingValue(tryRem.value);
        if (mp.find(corVal) == mp.end() || mp[corVal].empty()) {
            mp[tryRem.value].push_back(i);
        } else {
            table[i] = deck.GetAndRemoveTopCard();
            table[mp[corVal].back()] = deck.GetAndRemoveTopCard();
            tryRemoveIndex.push(i);
            tryRemoveIndex.push(mp[corVal].back());
            mp[corVal].pop_back();
            count++;
        }
    }
    return count;
}

```
