/*
  Motor Speed Control
  
  This program let's the user control the speed of a motor from the Serial Monitor

  Transitor Base Attached Pin 6 (This controls the motor)

  The circuit: 
  1 Power Transistor
  1 DC Motor
  
  Created 10/3/19
  By Miguel Osuna
  Modified: -/-/-
  By: -----------
*/

const int dcMotor = 6;

void setup()
{
    // Configure the transistor pin as an output
    pinMode(dcMotor, OUTPUT);

    // Display a message to the user
    Serial.begin(9600);
    Serial.print("Please enter a number between 0 and 9: ");
}

void loop()
{
    char userInput;

    //Check for an input from the user
    if(Serial.available() > 0)
    {
        // The user inputs a character
        userInput = Serial.read();

        if(userInput >= '0' && userInput <= '9')
        {
            int motorSpeed = userInput - '0';
            motorSpeed = map(motorSpeed, 0, 9, 0, 255);
            analogWrite(dcMotor, motorSpeed);
        }
    }
}

