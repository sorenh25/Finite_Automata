//main function to call nfa-dfa
#include "NFA.hpp"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
  NFA myFA(argv[1]);
  myFA.readNFA();
  myFA.convertToDFA();
  myFA.writeDFA();

}
