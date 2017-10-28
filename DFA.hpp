#include <string>
//#include <unordered_map>
#include <map>
#include <utility>
#include <vector>
#include <fstream>

class DFA {
public:
  DFA(std::string, std::string);
  ~DFA();
  void readDFA();
  void runInput();
  bool readInputString(std::ifstream& InputFile);
  void testInputString();

  bool validInput();
  bool isAcceptState();

  void printDFA();


//private:
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
  std::map<std::string, bool> endStates; //use at() operator to avoid default behaviour of []. at returns std::out_of_range is key is not found

  std::map<std::pair<std::string, char>, std::pair<std::string, int>> transitionFunction;

};
