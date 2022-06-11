#include <iostream>
#include <string>
#include "StateString.h"

/* CIS 25, Nicholas Roze-Freitas, this project implements a turing machine */

StateString::StateString(std::string state){
  // This function creates a new state with both of its instructions
  split(state); 
}

void StateString::split(std::string fullState){
  // This function splits splits and creates two instructions based off a state string
  int middleIndex = fullState.find(":"); 
  std::string leftInstructions = fullState.substr(STARTING_POSITION, middleIndex); 
  std::string rightInstructions = fullState.substr(middleIndex+1, fullState.size()); 
  Instruction leftHalf(leftInstructions); 
  Instruction rightHalf(rightInstructions); 
  stateInstruction.push_back(leftHalf); 
  stateInstruction.push_back(rightHalf); 
}