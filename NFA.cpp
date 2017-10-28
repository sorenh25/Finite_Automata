#include "NFA.hpp"
#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;


NFA::NFA(string FA) {
  FAFileName = FA;
}

NFA::~NFA() {

}



void NFA::readNFA() {

  ifstream FAFile;
  FAFile.open(FAFileName.c_str());
  if (!FAFile.is_open()) {
    cerr << "FA file could not be opened" << endl;
  }

  getline(FAFile, nameOfFA);

  string line;
  getline(FAFile,line,'\n');

  //this block reads in the alphabet
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
  alphabet.push_back('~'); //adds the empty string to the alphabet. I dont know whether that would be in the alphabet description of an NFA

  //This block reads in the NFAStates. Confirmed!
  getline(FAFile, line);
  if (line[line.length() - 1] == '\r') {
    line.pop_back();
  }
  size_t pos1 = 0;
  size_t pos2 = line.find_first_of(',', pos1);
  while(pos2 != string::npos) {
    NFAStates.push_back(line.substr(pos1,pos2 - pos1));
    pos1 = pos2 + 1;
    pos2 = line.find_first_of(',',pos1);
  }
  line = line.substr(pos1, line.length() - pos1);
  //line.pop_back();
  NFAStates.push_back(line);

  getline(FAFile, startState); //read startState. Confirmed
  if (startState[startState.length() - 1] == '\r') {
    startState.pop_back();
  }

  //Gets the accepting NFAStates. Should work same way as read NFAStates.
  getline(FAFile, line);
  if (line[line.length() - 1] == '\r') {
    line.pop_back();
  }
  pos1 = 0;
  pos2 = line.find_first_of(',', pos1);
  while(pos2 != string::npos) {
    endStates[line.substr(pos1,pos2 - pos1)] = true;
    NFAEndStates.push_back(line.substr(pos1,pos2 - pos1));
    pos1 = pos2 + 1;
    pos2 = line.find_first_of(',',pos1);
  }
  line = line.substr(pos1, line.length() - pos1);
  //line.pop_back();
  endStates[line] = true;
  NFAEndStates.push_back(line);

  string beginState, destinationState;
  char inputCharacter;

  //int ruleNumber = 0;
  while(!FAFile.eof()) {
    getline(FAFile, line);
    if (line.empty()) {
      //cout << "Read in an empty line, something is wrong" << endl;
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


    createTransitionFunction(beginState, inputCharacter, destinationState);
    //transitionFunction[make_pair(beginState,inputCharacter)] = make_pair(destinationState, ruleNumber);
    //ruleNumber++;
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

void NFA::createTransitionFunction(string beginState, char inputCharacter, string destinationState) {
  //map<std::pair<std::string, char>, std::vector<std::string>>::iterator itr;
  //itr = transitionFunction.find(make_pair(beginState, inputCharacter));
  //if (itr != transitionFunction.end()) {
  //  tra
  //}
  try {
    vector<string>& destinations = transitionFunction.at(make_pair(beginState, inputCharacter));
    if (inVector(destinationState, destinations)) {
      cout << "@@@" << beginState << ' ' << inputCharacter << ' ' << destinationState << endl;
      return;
    }
    destinations.push_back(destinationState);
    //transitionFunction.at(make_pair(beginState, inputCharacter)).push_back(destinationState);


  }
  catch (const out_of_range& oor) {
    transitionFunction[make_pair(beginState, inputCharacter)].push_back(destinationState);
  }

}

void NFA::printNFA() {
  cout << "####################" << endl;
  cout << nameOfFA << endl;

  cout << "Alphabet: ";
  for (unsigned int i = 0; i < alphabet.size(); i++) {
    cout << alphabet[i] << ' ';
  }
  cout << '(' << alphabet.size() << ')' << endl;

  cout << "NFAStates: ";
  for (unsigned int i = 0; i < NFAStates.size(); i++) {
    cout << NFAStates[i] << ' ';
  }
  cout << '(' << NFAStates.size() << ')' << endl;

  cout << "Start state: " << startState << endl;

  cout << "Accept NFAStates: ";
  /*map<std::string, bool>::iterator it = NFAEndStates.begin();
  int k = 0;
  for ( ; it != NFAEndStates.end(); it++) {
    k++;
    cout << it->first << ' ';
  }*/

  for (unsigned int i = 0; i < DFAEndStates.size(); i++) {
    if (i != 0) {
      cout << ',';
    }
    cout << '{' << DFAEndStates[i] << '}';
  }
  cout << endl;
  //cout << '(' << k << ')' << endl;

  for (unsigned int i = 0; i < NFAStates.size(); i++) {
    for (unsigned int j = 0; j < alphabet.size(); j++) {
      try {
        vector<string> desinations = transitionFunction.at(make_pair(NFAStates[i], alphabet[j]));
        cout << NFAStates[i] << ',' << alphabet[j];
        for (unsigned int k = 0; k < desinations.size(); k++) {
          cout << ',' << desinations[k];
        }
        cout << endl;
      }
      catch (const out_of_range& oor) {
        continue;
      }
    }
  }

  cout << "Epsilon: " << endl;
  for (unsigned int i = 0; i < NFAStates.size(); i++) {
    cout << "E(" << NFAStates[i] << ") = {";
    vector<string> eps = epsilon[NFAStates[i]];
    for (unsigned int j = 0; j < eps.size(); j++) {
      cout << eps[j];
    }
    cout << '}' << endl;
  }

  //map<std::pair<std::string, char>, std::vector<std::string>>::iterator itr;
  //itr = transitionFunction.begin();

  //for ( ; itr != transitionFunction.end(); itr++) {

  //}
  cout << endl << "Rules:" << endl;
  for (unsigned int i = 0; i < rules.size(); i++) {
    cout << rules[i] << endl;
  }

  cout << "####################" << endl;


}

bool NFA::inVector(string key, vector<string>& val) {
  for (unsigned int i = 0; i < val.size(); i++) {
    if (key == val[i]) {
      return true;
    }
  }
  return false;
}

void NFA::printVector(vector<string>& vec) {
  for (unsigned int i = 0; i < vec.size(); i++) {
    cout << vec[i] << ' ';
  }
  cout << endl;
}


void NFA::findEpsilon() {
  vector<string> destinations;
  //vector<string>& eps = destinations; //just because I can't inistantiate a reference without initializing it
  for (unsigned int i = 0; i < NFAStates.size(); i++) {

    try {
      destinations = transitionFunction.at(make_pair(NFAStates[i],'~'));
    }
    catch (const out_of_range& oor) {
      epsilon[NFAStates[i]].push_back(NFAStates[i]);
      continue;
    }
    vector<string>& eps = epsilon[NFAStates[i]];
    eps.push_back(NFAStates[i]);
    for (unsigned int j = 0; j < destinations.size(); j++) {
      if (inVector(destinations[j], eps)) {
        continue;
      }

      eps.push_back(destinations[j]);
    }
  }

  for (unsigned int i = 0; i < NFAStates.size(); i++) {
    vector<string>& eps = epsilon[NFAStates[i]];
    for (unsigned int j = 1; j < eps.size(); j++) {
      destinations = epsilon[eps[j]];
      for (unsigned k = 1; k < destinations.size(); k++) {
        if (!inVector(destinations[k],eps)) {
          eps.push_back(destinations[k]);
        }
      }
      sort(eps.begin(), eps.end());
    }
  }
}

void NFA::convertToDFA() {
  findEpsilon();
  vector<string> startStates;
  vector<string> destinationStates = epsilon[startState];
  string str = returnString(destinationStates);
  DFAStates.push_back(str);

  for (unsigned int i = 0; i < DFAStates.size(); i++) {
    if (DFAStates[i] == "TrapState") {
      continue;
    }
    startStates = returnStateVector(DFAStates[i]);
    findDestinations(startStates);
  }

  findEndStates();
  if (inVector("TrapState", DFAStates)) {
    for (unsigned int i = 0; i < alphabet.size(); i++) {
      if (alphabet[i] == '~') {
        continue;
      }
      DFATransitionFunction[make_pair("TrapState", alphabet[i])] = "TrapState";
    }
  }

}

string NFA::returnString(vector<string>& vec) {
  sort(vec.begin(), vec.end());
  string str = vec[0];
  for (unsigned int i = 1; i < vec.size(); i++) {
    str += ',' + vec[i];
  }
  return str;
}

void NFA::copyIntoVector(vector<string>& oldVec, vector<string>& newVec) {
  for (unsigned int i = 0; i < newVec.size(); i++) {
    if (!inVector(newVec[i], oldVec)) {
      oldVec.push_back(newVec[i]);
    }
  }
}

vector<string> NFA::returnStateVector(string str) {
  vector<string> vec;
  if (str[str.length() - 1] == '\r') {
    str.pop_back();
  }
  size_t pos1 = 0;
  size_t pos2 = str.find_first_of(',', pos1);
  while(pos2 != string::npos) {
    vec.push_back(str.substr(pos1,pos2 - pos1));
    pos1 = pos2 + 1;
    pos2 = str.find_first_of(',',pos1);
  }
  str = str.substr(pos1, str.length() - pos1);
  vec.push_back(str);

  return vec;
}

void NFA::findDestinations(vector<string> vec) {
  for (unsigned int i = 0; i < alphabet.size(); i++) {
    vector<string> destinationStates;
    if (alphabet[i] == '~') {
      continue;
    }
    for (unsigned int j = 0; j < vec.size(); j++) {
      try {
        copyIntoVector(destinationStates, transitionFunction.at(make_pair(vec[j], alphabet[i])));
      }
      catch(const out_of_range& oor) {
        continue;
      }
    }
    if (destinationStates.empty()) {
      DFATransitionFunction[make_pair(returnString(vec), alphabet[i])] = "TrapState";
      if (!inVector("TrapState", DFAStates)) {
        DFAStates.push_back("TrapState");
      }
      continue;
    }
    for (unsigned int k = 0; k < destinationStates.size(); k++) {
      copyIntoVector(destinationStates, epsilon[destinationStates[i]]);
    }

    string desStateStr = returnString(destinationStates);
    if (!inVector(desStateStr, DFAStates)) {
      DFAStates.push_back(desStateStr);
    }
    DFATransitionFunction[make_pair(returnString(vec), alphabet[i])] = desStateStr;
  }
}

void NFA::writeDFA() {
  outputFileName = "DFA" + FAFileName;
  ofstream DFAFile;
  DFAFile.open(outputFileName.c_str());

  DFAFile << "DFA version of: " << nameOfFA << endl;

  for (unsigned int i = 0; i < alphabet.size(); i++) {
    if (alphabet[i] == '~') {
      continue;
    }
    if (i != 0) {
      DFAFile << ',';
    }
    DFAFile << alphabet[i];
  }
  DFAFile << endl;

  for (unsigned int i = 0; i < DFAStates.size(); i++) {
    if (i != 0) {
      DFAFile << ',';
    }
    DFAFile << '{' << DFAStates[i] << '}';
  }
  DFAFile << endl;

  DFAFile << '{' << returnString(epsilon[startState]) << '}' << endl;

  sort(DFAEndStates.begin(), DFAEndStates.end());
  for (unsigned int i = 0; i < DFAEndStates.size(); i++) {
    if (i != 0) {
      DFAFile << ',';
    }
    DFAFile << '{' << DFAEndStates[i] << '}';
  }
  DFAFile << endl;


  string dstate;
  sort(DFAStates.begin(), DFAStates.end());

  for (unsigned int i = 0; i < DFAStates.size(); i++) {
    for (unsigned int j = 0; j < alphabet.size(); j++) {
      if (alphabet[j] == '~') {
        continue;
      }
      try {
        dstate = DFATransitionFunction.at(make_pair(DFAStates[i], alphabet[j]));
      }
      catch (const out_of_range oor) {
        continue;
      }
      DFAFile << '{' << DFAStates[i] << "}," << alphabet[j] << ",{" << dstate << '}' <<endl;
    }
  }
}

void NFA::findEndStates() {


  for (unsigned int i = 0; i < DFAStates.size(); i++) {
    if (DFAStates[i] == "TrapState") {
      continue;
    }
    //bool endState = false;
    vector<string> states = returnStateVector(DFAStates[i]);
    for (unsigned int j = 0; j < NFAEndStates.size(); j++) {
      if (inVector(NFAEndStates[j], states)) {
        DFAEndStates.push_back(DFAStates[i]);
        break;
      }
    }
  }
    //bool endstate = false;




/*
  for (unsigned int k = 0; k < destinationStates.size(); k++) {
    try {
      endstate = NFAEndStates.at(destinationStates[k]);
    }
    catch (const out_of_range oor) {
      continue;
    }
    if (endstate) {
      if (!inVector(desStateStr, DFAEndStates)) {
        DFAEndStates.push_back(desStateStr);
      }
      break;
    }

  }
  */

}
