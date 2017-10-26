#include "NFA.hpp"


using namespace std;


int main(int argc, char** argv) {
  NFA myFA(argv[1]);
  myFA.readNFA();
  myFA.findEpsilon();
  myFA.printNFA();

}
