//definition of nfa-dfa
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <fstream>

class NFA {
public:
  NFA(std::string);
  ~NFA();
  void readNFA(); //fucntion to call to read the nfa
  void convertToDFA(); //this function converts the nfa to a dfa
  void writeDFA(); // this function writes the DFA to a file


private:
  void createTransitionFunction(std::string, char, std::string);
  bool inVector(std::string, std::vector<std::string>&);
  std::string returnString(std::vector<std::string>&);
  void copyIntoVector(std::vector<std::string>&, std::vector<std::string>&);
  std::vector<std::string> returnStateVector(std::string);
  void printNFA();
  void printVector(std::vector<std::string>&);
  void findEpsilon();
  void findDestinations(std::vector<std::string>);
  void findEndStates();

  std::string FAFileName;
  std::string outputFileName;
  std::string nameOfFA;

  std::vector<char> alphabet;
  std::vector<std::string> NFAStates;
  std::vector<std::string> rules;
  std::string startState;
  std::map<std::string, bool> endStates;
  std::vector<std::string> NFAEndStates;

  std::map<std::pair<std::string, char>, std::vector<std::string>> transitionFunction; //structure contains the initial nfa
  std::map<std::string, std::vector<std::string>> epsilon;

  std::vector<std::string> DFAStates;
  std::vector<std::string> DFAEndStates;
  std::map<std::pair<std::string, char>, std::string> DFATransitionFunction; //structure contains the converted DFA

};
