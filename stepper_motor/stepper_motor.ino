/*
  5V Stepper Motor Controller
    
  This program allows the user to controls the speed and position of a 5V Stepper Motor

  ULN2003 Stepper Motor Driver Connections
  Pin IN1 - Arduino Pin 8
  Pin IN2 - Arduino Pin 9
  Pin IN3 - Arduino Pin 10
  Pin IN4 - Arduino Pin 11
  Pin A - Stepper Motor Blue Cable
  Pin B - Stepper Motor Pink Cable
  Pin C - Stepper Motor Yellow Cable
  Pin D - Stepper Motor Orange Cable

  The circuit:
  1 ULN2003 Stepper Motor Driver
  1 5V Stepper Motor

  Created 5/4/19
  By Miguel Osuna
  Modified: -/-/-
  By: -----------
*/

#include <Stepper.h>

// We define the stepper motor characteristics
const float stepsPerRev = 32;
const float gearReduction = 64;
const float stepsPerOutRev = stepsPerRev * gearReduction;

// We define the stepper motor pins
const int pinOne = 8;
const int pinTwo = 9;
const int pinThree = 10;
const int pinFour = 11;

// We define a Stepper class object
Stepper stepperMotor(stepsPerRev, pinOne, pinTwo, pinThree, pinFour);

void setup()
{
    pinMode(pinOne, OUTPUT);
    pinMode(pinTwo, OUTPUT);
    pinMode(pinThree, OUTPUT);
    pinMode(pinFour, OUTPUT);
}

void loop()
{
    int stepsRequired;
    // Slow start to observe the driver leds light up
    stepperMotor.setSpeed(1);
    stepsRequired = 4;
    stepperMotor.step(stepsRequired);
    delay(2000);

    // Rotate CW half turn slowly
    stepsRequired = stepsPerOutRev / 2;
    stepperMotor.setSpeed(100);
    stepperMotor.step(stepsPerOutRev);
    delay(1000);

    // Rotate CW half turn rapidly
    stepperMotor.setSpeed(500);
    stepperMotor.step(stepsPerOutRev);
    delay(1000);
}

