#include "DFA.hpp"
#include <iostream>
#include <utility>
#include <unordered_map>
#include <map>
#include <string>
using namespace std;


int main(int argc, char** argv) {
  FA myFA(argv[1], argv[2]);
  myFA.readFA();
  myFA.runInput();

}


/*
//DFA myDFA("hello", "world");

pair<string,char> mypair = make_pair("yay",'c');
cout << mypair.first << ' ' << mypair.second << endl;

map<pair<string,char>,string> myMap;

//myMap[make_pair("wow",'b')] = "interesting";
myMap[mypair] = "halloj";
myMap[make_pair("end",'a')] = "hejsa";
cout << myMap[mypair] << endl;
//mypair = make_pair("end",'a');
//cout << myMap[mypair] << endl;
cout << myMap[make_pair("end",'a')]  << endl;

///awduhaowuhdoahw
*/
