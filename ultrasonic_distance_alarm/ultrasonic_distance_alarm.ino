/*
  Ultra-sonic Distance Alarm

  This program turns on an alarm in case of an approach with various tones according to the object's distance.

  Piezo Buzzer Asigned to Pin 6
  Red LED Asigned to Pin 7
  Green LED Asigned to Pin 8
  Ultrasonic Sensor Asigned to Pin 9 and 10 (Echo and Trigger respectively)
  Liquid Crytal Display Pins:

       LCD RS pin to digital pin 12
       LCD Enable pin to digital pin 11
       LCD D4 pin to digital pin 2
       LCD D5 pin to digital pin 3
       LCD D6 pin to digital pin 4
       LCD D7 pin to digital pin 5

       LCD R/W pin to ground
       LCD VSS pin to ground
       LCD VCC pin to 5V

  The circuit:
  1 Red LED
  1 Green LED
  2 Resistors
  1 Piezo Buzzer
  1 Digital LCD
  1 Ultra-sonic sensor
  1 Potentiometer

  Created 11/3/19
  By Miguel Osuna
  Modified: -/-/-
  By: -----------
*/
#include <LiquidCrystal.h>

// Setting all the component pins
const int buzzerPin = 6;
const int redLed = 7;
const int greenLed = 8;
const int triggerPin = 9;
const int echoPin = 10;

const int rsPin = 12;
const int enPin = 11;
const int d4Pin = 5;
const int d5Pin = 4;
const int d6Pin = 3;
const int d7Pin = 2;

// Now we define an LCD object with the pins specified
// This is the 4 bit mode
LiquidCrystal lcd(rsPin, enPin, d4Pin, d5Pin, d6Pin, d7Pin);

void setup()
{
  //We set up Trigger Pin as an Output and Echo Pin as an Input
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set up the LCD's columns and rows in order
  lcd.begin(16, 2);
  // Print a message to the LED
  // It sets on 0,1 automatically
  lcd.print("Starting sensor...");
  Serial.begin(9600);
}

void loop()
{
  // Local variables that we will need for the loop
  int timeDuration = 0;
  int distance = 0;
  int timeDelay = 0;

  // First, we setup everything for the trigger square signal
  // The square signal has to have a length of 10 us in order to start the sensing
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Start to take time when it goes from LOW to HIGH, and stop counting until it reaches LOW again.
  timeDuration = pulseIn(echoPin, HIGH);

  // Then we convert the total time to the distance between the sensor and the object
  // We convert to cm, multiplying us * cm/us
  // The time needs to be divided by 2, because it's only one distance
  distance = objectDistance(timeDuration);
  // We convert the value to a positive one
  distance *= -1;

  // We clear the content in the LCD in order to display again

  Serial.println(distance);
  lcd.clear();
  lcd.setCursor(0, 0);

  // Alarm sequences
  if(distance < 0 || distance > 200)
  {
      lcd.print("Out of range...");
      lcd.setCursor(0,1);
      lcd.print("Don't worry");
  }

  else
  {
    lcd.print("Object In-range");
    lcd.setCursor(0, 1);
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.print(" cm");
  
    // If objetc's distance isn't within danger range
    if (distance >= 50)
    {
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, HIGH);
      noTone(buzzerPin);
    }
  
    // If objetc's distance is within danger range
    else
    {
      digitalWrite(greenLed, LOW);
  
      if (distance < 15)
      {
        timeDelay = 1;
        tone(buzzerPin, 4000);
        digitalWrite(redLed, HIGH);
        delay(timeDelay);
      }
  
      if (distance >= 15 && distance < 30)
      {
        timeDelay = 2;
        tone(buzzerPin, 2500);
        digitalWrite(redLed, HIGH);
        delay(timeDelay);
      }
  
      if (distance >= 30 && distance < 50)
      {
        timeDelay = 3;
        tone(buzzerPin, 1000);
        digitalWrite(redLed, HIGH);
        delay(timeDelay);
      }
  
      noTone(buzzerPin);
      digitalWrite(redLed, LOW);
      delay(timeDelay);
    }
  }
}

int objectDistance(int timeDuration)
{
  int distance = 0;
  distance = (timeDuration / 2) * (343 * 100 / 1e06);
  return distance;
}

int chooseDelay(int num)
{
  int timeDelay = 0;
  switch (num)
  {
    case 1:
      timeDelay = 500;
      break;
    case 2:
      timeDelay = 750;
      break;
    case 3:
      timeDelay = 1000;
      break;
    default:
      break;
  }
  return timeDelay;
}
