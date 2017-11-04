//main function to call DFA solver
#include "DFA.hpp"
#include <iostream>
#include <utility>
#include <unordered_map>
#include <map>
#include <string>
using namespace std;


int main(int argc, char** argv) {
  DFA myDFA(argv[1], argv[2]);
  myDFA.readDFA();
  myDFA.runInput();

}
