#include "DFA.hpp"
#include "string"
#include "iostream"
#include "stdexcept"


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
  if (line[line.length() - 1] == '\r') {
    line.pop_back();
  }
  for (unsigned int i = 0; i < line.length(); i++) { //Confirmed!
    if (line[i] == ',') {
      continue;
    }
    else {
      alphabet.push_back(line[i]);
    }
  }
  //This block reads in the states. Confirmed!
  getline(FAFile, line);
  if (line[line.length() - 1] == '\r') {
    line.pop_back();
  }
  size_t pos1 = 0;
  size_t pos2 = line.find_first_of(',', pos1);
  while(pos2 != string::npos) {
    states.push_back(line.substr(pos1,pos2 - pos1));
    pos1 = pos2 + 1;
    pos2 = line.find_first_of(',',pos1);
  }
  line = line.substr(pos1, line.length() - pos1);
  //line.pop_back();
  states.push_back(line);

  getline(FAFile, startState); //read startState. Confirmed
  if (startState[startState.length() - 1] == '\r') {
    startState.pop_back();
  }

  //Gets the accepting states. Should work same way as read states.
  getline(FAFile, line);
  if (line[line.length() - 1] == '\r') {
    line.pop_back();
  }
  pos1 = 0;
  pos2 = line.find_first_of(',', pos1);
  while(pos2 != string::npos) {
    endStates[line.substr(pos1,pos2 - pos1)] = true;
    pos1 = pos2 + 1;
    pos2 = line.find_first_of(',',pos1);
  }
  line = line.substr(pos1, line.length() - pos1);
  //line.pop_back();
  endStates[line] = true;;

  string beginState, destinationState;
  char inputCharacter;
  //getline(FAFile, line);
  int ruleNumber = 0;
  while(!FAFile.eof()) {
    getline(FAFile, line);
    if (line.empty()) {
      cout << "Read in an empty line, something is wrong" << endl;
      break;
    }
    if (line[line.length() - 1] == '\r') {
      line.pop_back();
    }
    rules.push_back(line);
    pos1 = 0;
    pos2 = line.find_first_of(',', pos1);
    beginState = line.substr(pos1, pos2);
    inputCharacter = line[pos2 + 1];
    destinationState = line.substr(pos2 + 3, line.length());

    transitionFunction[make_pair(beginState,inputCharacter)] = make_pair(destinationState, ruleNumber);

    //getline(FAFile, line);
    ruleNumber++;
    /*
    cout << "Begin: " << beginState << endl;
    cout << "Input: " << inputCharacter << endl;
    cout << "Destination: " << destinationState << endl;
    cout << "Line length: " << line.length() - 2 << endl; //minus 2 because of the commas
    cout << endl;
    */

  }


  FAFile.close();

}

void FA::runInput() {
  ifstream InputFile;
  InputFile.open(inputFileName.c_str());
  if (!InputFile.is_open()) {
    cerr << "InputFile file could not be opened" << endl;
  }
  printFA();

  while(readInputString(InputFile)) {
    testInputString();
  }


  InputFile.close();
}

bool FA::readInputString(ifstream& InputFile) {
  if (InputFile.eof()) {
    return false;
  }
  getline(InputFile, inputString);
  if (inputString.empty()) {
    return false;
  }
  if (inputString[inputString.length() - 1] == '\r') {
    inputString.pop_back();
  }
  //cout << "Input line: " << inputString << endl;
  //cout << "Input length: " << inputString.length() << endl << endl;
  return true;
}

void FA::testInputString() {
  currentState = startState;
  if (!validInput()) {
    cerr << "Input given not valid" << endl;
    return;
  }
  pair<string, int> destinationPair;
  for (unsigned int i = 0; i < inputString.length(); i++) {
    try {
      destinationPair = transitionFunction.at(make_pair(currentState,inputString[i]));
    }
    catch (const out_of_range& oor) {
      cout << "reject" << endl;
      //cout << "Input: " << inputString[i] << endl;
      //cout << "current State: " << currentState << " (" << currentState.length() << ')' << endl;
      //cout << destinationPair.first << " " << destinationPair.first.length() << endl;

      //cerr << "Transition function does not contain given input, state combination: " << currentState << inputString[i] << endl;
      //cerr << oor.what() << endl;
      return;
    }
    cout << "Rule " << destinationPair.second << ':' << rules[destinationPair.second] << endl;
    currentState = destinationPair.first;
  }

  try {
    endStates.at(currentState);
  }
  catch (const out_of_range& oor) {
    cout << "reject" << endl;
    return;
  }
  cout << "accept" << endl;






}

bool FA::validInput() {
  alphabet.shrink_to_fit();
  /*
  for (unsigned int i = 0; i < alphabet.size(); i++) {
    cout << alphabet[i] << ' ';
  }
  cout << "Done" << endl;
  */

  for (unsigned int i = 0; i < inputString.length(); i++) {
    for (unsigned int j = 0; j < alphabet.size(); j++) {
      if (inputString[i] == alphabet[j]) {
        break;
      }
      if (j == alphabet.size() - 1) {
        return false;
      }
    }
  }
  return true;
}

bool FA::isAcceptState() {
  return true;
}

void FA::printFA() {
  cout << "####################" << endl;
  cout << nameOfFA << endl;

  cout << "Alphabet: ";
  for (unsigned int i = 0; i < alphabet.size(); i++) {
    cout << alphabet[i] << ' ';
  }
  cout << '(' << alphabet.size() << ')' << endl;

  cout << "States: ";
  for (unsigned int i = 0; i < states.size(); i++) {
    cout << states[i] << ' ';
  }
  cout << '(' << states.size() << ')' << endl;

  cout << "Start state: " << startState << endl;

  cout << "Accept States: ";
  map<std::string, bool>::iterator it = endStates.begin();
  int k = 0;
  for ( ; it != endStates.end(); it++) {
    k++;
    cout << it->first << ' ';
  }
  cout << '(' << k << ')' << endl;

  cout << "Rules:" << endl;
  for (unsigned int i = 0; i < rules.size(); i++) {
    cout << rules[i] << endl;
  }

  cout << "####################" << endl;


}
