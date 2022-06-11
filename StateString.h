#ifndef STATESTRINGTYPE_H
#define STATESTRINGTYPE_H
#include <iostream>
#include <vector>
#include "Instruction.h"

/* CIS 25, Nicholas Roze-Freitas, this project implements a turing machine */


const int STARTING_POSITION = 0;

class StateString {
// This class creates an object called state string which contains a vector of two instructions on what to do if theres a mark or not
public:
  StateString(std::string state); 
  void split(std::string fullStateString);
  std::vector<Instruction> stateInstruction; 
};

#endif