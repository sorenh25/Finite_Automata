#include <string>
#include <map>
#include <utility>
#include <vector>
#include <fstream>

class NFA {
public:
  NFA(std::string);
  ~NFA();
  void readNFA();
  void createTransitionFunction(std::string, char, std::string);

  bool inVector(std::string, std::vector<std::string>&);
  std::string returnString(std::vector<std::string>&);
  void copyIntoVector(std::vector<std::string>&, std::vector<std::string>&);
  std::vector<std::string> returnStateVector(std::string);

  //void runInput();
  //bool readInputString(std::ifstream& InputFile);
  //void testInputString();

  //bool validInput();
  //bool isAcceptState();

  void printNFA();
  void printVector(std::vector<std::string>&);


  void convertToDFA();
  void findEpsilon();
  void findDestinations(std::vector<std::string>);

  void writeDFA();


private:
  std::string FAFileName;
  //std::string inputFileName;
  std::string outputFileName;

  std::string nameOfFA;
  //std::string currentState;
  //std::string inputString;

  std::vector<char> alphabet;
  std::vector<std::string> NFAStates;
  std::vector<std::string> rules;
  std::string startState;
  std::map<std::string, bool> NFAEndStates; //use at() operator to avoid default behaviour of []. at returns std::out_of_range is key is not found

  std::map<std::pair<std::string, char>, std::vector<std::string>> transitionFunction;
  std::map<std::string, std::vector<std::string>> epsilon;

  std::vector<std::string> DFAStates;
  std::map<std::pair<std::string, char>, std::string> DFATransitionFunction;

};
