#ifndef TURINGTYPE_H
#define TURINGTYPE_H
#include <iostream>
#include <vector>
#include "StateString.h"

/* CIS 25, Nicholas Roze-Freitas, this project implements a turing machine */

const char COMMA = ',';
const char MINUS = '-';
const int MIN_TAPE_SIZE = 1;
const int STARTING_STATE = 1;
const int TAPE_START_POSITION = 0;
const int ENDING_STATE = 0;
const int STATE_INSTRUCTION_ONE = 0;
const int STATE_INSTRUCTION_TWO = 1;
class TuringMachine{
public:
  TuringMachine();
  TuringMachine(std::string tape_file, std::string state_file);
  void move_left();   
  void move_right();  
  bool read_square();  
  void make_mark();    
  void remove_mark(); 
  std::string get_tape();  
  void sort_tape();
  bool check_mark(); 
  void update(); 
  void read_instruction(Instruction instruction); 
  void run(); 
  int currentState; 
private:
  Instruction state_to_instruction(int desiredState, bool isMark);
  std::vector<StateString> stateInstructions;
  void set_tape(std::string tape);
  int tapePosition; 
  std::vector<int> onePositions; 
};
#endif 