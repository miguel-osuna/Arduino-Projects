/*
  4x4 Keypad Test 

  Keypad Pinout
  Pin R1 - Arduino Pin 9
  Pin R2 - Arduino Pin 8
  Pin R3 - Arduino Pin 7
  Pin R4 - Arduino Pin 6

  Pin C1 - Arduino Pin 5
  Pin C2 - Arduino Pin 4
  Pin C3 - Arduino Pin 3
  Pin C2 - Arduino Pin 2

  The circuit:  
  1 4x4 Keypad

  Created 29/3/19
  By Miguel Osuna
  Modified: 5/4/2019
  By: -----------
*/

#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }
}

