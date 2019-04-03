/*
  LED Brightness Control
  
  This program let's the user control the LED brightness with a Potentiometer.

  Potentiometer Asigned to Pin A0
  Push-button Asigned to Pin 7
  LED to Pin 6

  The circuit: 
  1 LED
  1 Push-button
  1 Potentiometer

  Connect Pin 1 of the Potentiometer to GND
  Connect Pin 2 of the Potentiometer to A0
  Connect Pin 3 of the Potentiometer to VCC

  Created 10/3/19
  By Miguel Osuna
  Modified: -/-/-
  By: -----------
*/

#define ledPin 6
#define buttonPin 7
#define potPin A0

void setup()
{
    // Define all the components
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(potPin, INPUT);
}

void loop()
{ 
    // Read the values from both the Potenciometer and the Push-button
    int reading = analogRead(potPin);
    int buttonStatus = digitalRead(buttonPin);

    // Convert from 10 bit resolution, to 8 bit resolution
    reading = map(reading, 0, 1024, 0, 255);

    // Write the PWM value converted from the Potentiometer into the LED
    if(buttonStatus == LOW)
        analogWrite(ledPin, reading);
    else
        digitalWrite(ledPin, LOW);
}

