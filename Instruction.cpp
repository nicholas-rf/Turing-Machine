#include <iostream>
#include <string>
#include "Instruction.h"

/* CIS 25, Nicholas Roze-Freitas, this project implements a turing machine */

Instruction::Instruction(std::string splitStateString) {
  // This function creates an instruction object with a string of instructions 
  uninterpretedInstruction = splitStateString; 
  get_mark(); 
  get_next_state();
  get_direction(); 
}

void Instruction::get_mark(){
  // This function checks if the mark instruction specifies the next space to be marked or not
  char markInstruction = uninterpretedInstruction[MARK_INSTRUCTON]; 
  if (markInstruction - ASCII_TO_INT_SUBTRACTION == DONT_MARK){ 
    mark = false; 
  } else if (markInstruction - ASCII_TO_INT_SUBTRACTION == MARK) { // This asks if string to integer ("markInstruction") is 1 which means  mark
    mark = true; // sets mark
  }
}

void Instruction::get_next_state(){
  // This function gets the next state number as specified in the instruction string
  char nextStateChar = uninterpretedInstruction[NEXT_STATE_INSTRUCTIOn]; 
  int nextStateNum = nextStateChar - ASCII_TO_INT_SUBTRACTION; 
  nextState = nextStateNum; 
}

void Instruction::get_direction(){
  // This function gets what direction is specified in the instruction string split
  if (uninterpretedInstruction[DIRECTION_INSTRUCTION] == RIGHT) { direction = RIGHT; } 
  else if (uninterpretedInstruction[DIRECTION_INSTRUCTION] == LEFT) { direction = LEFT; } 
}
