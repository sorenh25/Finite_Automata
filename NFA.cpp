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

  //int ruleNumber = 0;
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

  for (unsigned int i = 0; i < states.size(); i++) {
    for (unsigned int j = 0; j < alphabet.size(); j++) {
      try {
        vector<string> desinations = transitionFunction.at(make_pair(states[i], alphabet[j]));
        cout << states[i] << ',' << alphabet[j];
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
  for (unsigned int i = 0; i < states.size(); i++) {
    cout << "E(" << states[i] << ") = {";
    vector<string> eps = epsilon[states[i]];
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
  for (unsigned int i = 0; i < states.size(); i++) {

    try {
      destinations = transitionFunction.at(make_pair(states[i],'~'));
    }
    catch (const out_of_range& oor) {
      epsilon[states[i]].push_back(states[i]);
      continue;
    }
    vector<string>& eps = epsilon[states[i]];
    eps.push_back(states[i]);
    for (unsigned int j = 0; j < destinations.size(); j++) {
      if (inVector(destinations[j], eps)) {
        continue;
      }
      eps.push_back(destinations[j]);
    }
  }

  for (unsigned int i = 0; i < states.size(); i++) {
    vector<string>& eps = epsilon[states[i]];
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
