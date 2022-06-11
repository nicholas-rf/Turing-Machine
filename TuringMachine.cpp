#include <iostream>
#include <fstream>
#include <algorithm>
#include "TuringMachine.h"

/* CIS 25, Nicholas Roze-Freitas, this project implements a turing machine */

TuringMachine::TuringMachine(){
  // This function creates a turing machine with a starting position on the tape of 0
  tapePosition = STARTING_POSITION;
}
TuringMachine::TuringMachine(std::string tape_file, std::string state_file) {
  // This function creates a turing machine object with its tape set up based on tape_file, and a set of instructions based on state_file
  std::ifstream tape(tape_file);
  std::ifstream state(state_file);
  currentState = STARTING_STATE;
  int stateCounter = STARTING_POSITION;
  if (state){
    while(!state.eof()) {
      std::string currentLine;
      std::getline(state, currentLine);
      stateInstructions.push_back(StateString(currentLine));
      stateCounter++;
    }
  } else {
    std::cerr << "State file doesn't exist" << std::endl;
  }
  
  if (tape) {
    std::string startingTape;
    std::getline(tape, startingTape);
    if (startingTape == ""){
      tapePosition = STARTING_POSITION;
    } else {
      set_tape(startingTape);
    }

  } else {
    tapePosition = STARTING_POSITION;
  }
  tape.close();
  state.close();

}
void TuringMachine::sort_tape(){
  // This function sorts the tape
  sort(onePositions.begin(), onePositions.end());
}
void TuringMachine::set_tape(std::string tape){ 
  // This function reads the tape specified in tape file and sets the initial condition for the machine before running
  int splitIndex = tape.find(":");
  std::string leftHalf = tape.substr(0, splitIndex);
  std::string rightHalf = tape.substr(splitIndex+1, tape.size());
  if (leftHalf[STARTING_POSITION] == MINUS) {
    tapePosition = (leftHalf[STARTING_POSITION+1] - ASCII_TO_INT_SUBTRACTION) * -1;
  } else {
    tapePosition = leftHalf[STARTING_POSITION] - ASCII_TO_INT_SUBTRACTION;
  }
  for (int position = STARTING_POSITION; position < rightHalf.size(); position++) {
    char markPos = rightHalf[position];
    std::cout << rightHalf[position] << std::endl;
    if (rightHalf[position] != COMMA){
      if (rightHalf[position] == MINUS) {
        onePositions.push_back((rightHalf[position+1] - ASCII_TO_INT_SUBTRACTION) * -1);
        position++;
      } else {
        onePositions.push_back(rightHalf[position] - ASCII_TO_INT_SUBTRACTION);
      }
    }
  }
}
void TuringMachine::move_left(){
  // This function moves the read head 1 square left
  tapePosition--;
}
void TuringMachine::move_right(){
  // This function moves the read head 1 square right
  tapePosition++;
}   
bool TuringMachine::read_square(){
  // This function reads the square and returns true if theres a mark, false otherwise
  for(int position = STARTING_POSITION; position < onePositions.size(); position++){
    if (tapePosition == onePositions[position]){
      return true;
    }
  }
  return false;
}  
void TuringMachine::make_mark(){
  // This function marks the square if otherwise not marked
  if(!read_square()){
    onePositions.push_back(tapePosition);
  } else {
    return;
  }
}   
void TuringMachine::remove_mark(){
  // This function removes the mark from the positions
  for(int position = STARTING_POSITION; position < onePositions.size(); position++){ 
    if(onePositions[position] == tapePosition){ 
      onePositions.erase(onePositions.begin()+position); 
      return;
    }
  }
}  
std::string TuringMachine::get_tape(){
  // This function returns a string representation of the tape
  sort_tape();
  std::string tape_representation = "[";
  if (onePositions.size() >= MIN_TAPE_SIZE){
    for(int position = STARTING_POSITION; position < onePositions.size(); position++){
      tape_representation += std::to_string(onePositions[position]);
      if (position == onePositions.size()-1){
        tape_representation += "]";
      } else {
        tape_representation += ", ";
      }  
    }
  } else {
    tape_representation = "[";
    tape_representation += std::to_string(onePositions[STARTING_POSITION]);
    tape_representation += "]";
  }
  return tape_representation;
}  
Instruction TuringMachine::state_to_instruction(int desiredState, bool isMark){
  // This function takes the state you want an instruction for and returns the corresponding instruction based off if theres a mark or not
  StateString newState = stateInstructions[desiredState-1]; 
  if (!isMark) {
    return newState.stateInstruction[STATE_INSTRUCTION_ONE];
  } else if (isMark) {
    return newState.stateInstruction[STATE_INSTRUCTION_TWO];
  }
}
void TuringMachine::read_instruction(Instruction instruction){
  // This function reads instructions and causes the machine to do things based off of instructions
  if(instruction.mark){ 
    make_mark();
  } else if (!instruction.mark) {
    remove_mark();
  }
  if (instruction.direction == RIGHT) {
    move_right(); 
  } else if (instruction.direction == LEFT) {
    move_left();
  }
  currentState = instruction.nextState; 
}
void TuringMachine::update(){
  // This function reads an instructon and makes changes on the tape based on it
  Instruction currentInstruction = state_to_instruction(currentState, read_square()); 
  read_instruction(currentInstruction);
}  
void TuringMachine::run(){
  // This function runs the turing machine until its state is 0
  currentState = STARTING_STATE;
  while(currentState != ENDING_STATE){
    update();
  }
}