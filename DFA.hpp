#include <string>
//#include <unordered_map>
#include <map>
#include <utility>
#include <vector>

class FA {
public:
  FA(std::string, std::string);
  ~FA();
  void readFA();


//private:
  std::string FAFileName;
  std::string inputFileName;
  std::string outputFileName;

  std::string nameOfFA;
  std::string currentState;

  std::vector<char> alphabet;
  std::vector<std::string> states;
  std::string startState;
  std::map<std::string, bool> endStates; //use at() operator to avoid default behaviour of []. at returns std::out_of_range is key is not found

  std::map<std::pair<std::string,char>,std::string> transitionFunction;

};
