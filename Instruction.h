#ifndef INSTRUCTIONTYPE_H
#define INSTRUCTIONTYPE_H
#include <iostream>

/* CIS 25, Nicholas Roze-Freitas, this project implements a turing machine */

const char RIGHT = 'R';
const char LEFT = 'L';
const int ASCII_TO_INT_SUBTRACTION = 48;
const int MARK_INSTRUCTON = 0;
const int DONT_MARK = 0;
const int MARK = 1;
const int DIRECTION_INSTRUCTION = 2;
const int NEXT_STATE_INSTRUCTIOn = 4;
class Instruction {
// An instruction class that allows for the creation of objects of instructions
  public:
      Instruction(std::string splitStateString);  
      std::string uninterpretedInstruction; 
      void get_direction(); 
      void get_mark(); 
      void get_next_state(); 
      bool mark;  
      char direction; 
      int nextState;
};

#endif
