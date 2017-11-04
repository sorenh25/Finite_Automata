//Class definition of the DFA class
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <fstream>

class DFA {
public:
  DFA(std::string, std::string);
  ~DFA();
  void readDFA(); //function to read the DFA
  void runInput(); //function to run input against the DFA.

private:
  bool readInputString(std::ifstream& InputFile);
  void testInputString();
  bool validInput();
  bool isAcceptState();
  void printDFA();

  std::string FAFileName;
  std::string inputFileName;
  std::string outputFileName;

  std::string nameOfFA;
  std::string currentState;
  std::string inputString;

  std::vector<char> alphabet;
  std::vector<std::string> states;
  std::vector<std::string> rules;
  std::string startState;
  std::map<std::string, bool> endStates;

  std::map<std::pair<std::string, char>, std::pair<std::string, int>> transitionFunction; //map used for transition function

};
