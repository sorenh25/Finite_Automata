main: dfa nfa

dfa: dfa-teamSorenHolm.cpp DFA.o
	g++ -Wall dfa-teamSorenHolm.cpp DFA.o -std=gnu++11 -static-libstdc++ -o dfa-teamSorenHolm

DFA.o: DFA.cpp DFA.hpp
	g++ DFA.cpp -Wall -c -std=gnu++11 -static-libstdc++

run: main
	DFA.out M1.txt M1-Accept.txt

nfa: nfa2dfa-teamSorenHolm.cpp NFA.o
	g++ -Wall nfa2dfa-teamSorenHolm.cpp NFA.o -std=gnu++11 -static-libstdc++ -o nfa2dfa-teamSorenHolm

NFA.o: NFA.cpp NFA.hpp
	g++ NFA.cpp -Wall -c -std=gnu++11 -static-libstdc++
