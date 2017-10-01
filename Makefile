main: main.cpp DFA.o
	g++ -Wall main.cpp DFA.o -std=gnu++11 -static-libstdc++ -o DFA.out

DFA.o: DFA.cpp DFA.hpp
	g++ DFA.cpp -Wall -c -std=gnu++11 -static-libstdc++

run: main
	DFA.out M1.txt M1-Accept.txt
