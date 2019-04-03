/*
  Servomotor Controlled with Joystick
    
  This program allows the user to control the position of a Servomotor with a Joystick

  Joystick Connections
  GND - Arduino GND
  +5V - Arduino Vcc (5V)
  VRx - A1
  VRy - A0
  SW - NC

  Servomotor Connections
  GND - Arduino GND
  +5V - Arduino Vcc (5V)
  Signal - Arduino Pin 6 (PWM)

  The circuit:  
  1 Joystick
  1 Servomotor

  Created 28/3/19
  By Miguel Osuna
  Modified: -/-/-
  By: -----------
*/

#include <Servo.h>

// Creates a servo object to control a servomotor
Servo myServo;

// Setup the Joystick and Servo Pins
const int verticalAxis =  A0;
const int horizontalAxis = A1;
const int pushButton = A2;
const int servoPin = 9;

int horizontalValue = 0;
int verticalValue = 0;
int buttonState;

void setup()
{
    pinMode(verticalAxis, INPUT);
    pinMode(horizontalAxis, INPUT);
    pinMode(pushButton, INPUT_PULLUP);
    
    pinMode(A3, OUTPUT);
    digitalWrite(A3, HIGH);
    
    Serial.begin(9600);
    myServo.attach(servoPin);
}

void loop()
{
    horizontalValue = analogRead(horizontalAxis);
    verticalValue = analogRead(verticalAxis);
    buttonState = digitalRead(pushButton);
    
    Serial.print("X-axis value: ");
    Serial.print(horizontalValue);
    Serial.print("  ");
    Serial.print("Y-axis value: ");
    Serial.println(verticalValue);

    if(buttonState == false)
    {
        horizontalValue = map(horizontalValue, 0, 1024, 0, 180);
        myServo.write(horizontalValue);  
        delay(15);
    }

    if(buttonState == true)
    {
        verticalValue = map(verticalValue, 0, 1024, 0, 180);
        myServo.write(verticalValue);\
        delay(15);
    }

}
