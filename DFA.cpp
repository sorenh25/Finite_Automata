#include "DFA.hpp"
#include "string"
#include "iostream"
#include <fstream>

using namespace std;

FA::FA(string FA, string input) {
  FAFileName = FA;
  inputFileName = input;
}

FA::~FA() {

}

void FA::readFA() {

  ifstream FAFile;
  FAFile.open(FAFileName.c_str());
  if (!FAFile.is_open()) {
    cerr << "DFA file could not be opened" << endl;
  }

  getline(FAFile, nameOfFA);

  string line;
  getline(FAFile,line,'\n');

  //this block read in the alphabet
  for (unsigned int i = 0; i < line.length() - 1; i++) { //so that the \n character is not part of the alphabet. Confirmed!
    if (line[i] == ',') {
      continue;
    }
    else {
      alphabet.push_back(line[i]);
    }
  }
  //This block reads in the states. Confirmed!
  getline(FAFile, line);
  cout << line << endl;
  size_t pos1 = 0;
  size_t pos2 = line.find_first_of(',', pos1);
  while(pos2 != string::npos) {
    states.push_back(line.substr(pos1,pos2 - pos1));
    pos1 = pos2 + 1;
    pos2 = line.find_first_of(',',pos1);
  }
  line = line.substr(pos1, pos2);
  line.pop_back();
  states.push_back(line);

  getline(FAFile, startState); //read startState. Confirmed
  startState.pop_back();

  //Gets the accepting states. Should work same way as read states.
  getline(FAFile, line);
  cout << line << endl;
  size_t pos1 = 0;
  size_t pos2 = line.find_first_of(',', pos1);
  while(pos2 != string::npos) {
    endStates[line.substr(pos1,pos2 - pos1)] = true;
    pos1 = pos2 + 1;
    pos2 = line.find_first_of(',',pos1);
  }
  line = line.substr(pos1, pos2);
  line.pop_back();
  endStates.[line] = true;;



}
