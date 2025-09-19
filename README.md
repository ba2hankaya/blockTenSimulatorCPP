# blockTenSimulatorCPP
This project includes a simulator that simulates x number of games of Block Ten and produces data, distributing the work accross threads. This data can then be analysed and processed through the analyser scripts in the analyse folder.

## Block Ten
The goal in Block Ten is to remove all cards from the deck. It is a really luck dependant game.

Setup:

	Type of Deck : Standard Deck

	Tableau: 9 piles. Each Tableu pile is dealt one card face up.

Rules:

	1) You can remove cards in pairs that add up to ten.

	2) Tens cannot be removed.

	3) Jack, Queens, and Kings are removed in pairs.

	4) Empty slots left by removing pairs are automatically filled by cards from the deck.

## How and why it's made
Tech used: c++, python
I decided to make this project after coming across the card game once where it was pre-installed on my Ubuntu OS. Because it is a pre-determined game where the user input doesn't change the outcome of the game, I wondered what the possibility of a win or progressing was, and what would be a reasonable increment of reward for each match to bring the win rate of the game to around %50. Then I initially made a simple c# script to reach the answer. After learning cpp and gaining more programming language I decided to make an advanced version of it, this time structuring the project better and using threads to be able to simulate more games at the same time. I also made some pyhton scripts to analyze the data the simulator spat out to analyze it better.

## Optimizations
I made a few versions of the algorithm for counting matches: only tracking the swapped cards, using a semi optimized way(time complexity wise) and most optimal(time complexity wise) algorithm I could come up with(in simulator/performance_notes.md) for matching cards in this manner. However, the fastest results were produced with the current version of the code which doesn't use any advanced data structures. It just loops through the table each iteration and removes a pair. More on this under lessons learned header. Also, instead of using mutex synchronizing methods to access the shared resources, I made every thread produce its own local results and merged the individual results at the end since the global result can only have up to 21 entries and the merging operation is cheaper than multiple threads trying to access a shared source.

## Lessons Learned
After researching why lower time complexity move count algorithms produced slower results I reached this conclusion. Because the brute force method doesn't create and move around data structures, its overhead is much smaller across a small array(9 values in this case). To test this theory I increased the deck card count and table length to hundreds and thousands and in that scenario the lower time complexity algorithms were much faster, confirming my conclusion. I also learned at an introductory level how to process and display data using python.
