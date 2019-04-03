/*
  Push-Button Interrupt Example
 
  An interrupt is attached to a push-button so it can be monitored
  
  Push-button Asigned to Pin 2 (INT-0)

  The circuit: 
  1 Push-button
  1 LED

  Created 11/3/19
  By Miguel Osuna
  Modified: -/-/-
  By: -----------
*/

const byte buttonPin = 2;
const byte ledPin = 13;
volatile byte buttonState = LOW;

void setup()
{
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);
    //digitalWrite(ledPin, LOW);

    // We use the first parameter to indicate the Interrupt Pin
    // The second parameter is the name of the Interrupt Service Routine
    // The third parameter is to activate the interrupt when there is a change from HIGH to LOW and from LOW to HIGH
    attachInterrupt(digitalPinToInterrupt(buttonPin), toggleLed, CHANGE);
}

void loop()
{
    // We toggle the LED by changing the button state with the ISR
    digitalWrite(ledPin, buttonState);
}

void toggleLed()
{
    // Negate the button state
    buttonState = !buttonState;
}

