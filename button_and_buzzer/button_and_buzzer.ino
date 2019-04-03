/*
  Controlling Piezo Buzzer With a Push Button Switch
  
  This program reproduces a frequency when pressing a push-button
  
  Piezo Asigned to Pin 13
  Push-button Asigned to Pin 12

  The circuit: 
  1 Piezo Buzzer
  1 Push-button

  Created 10/3/19
  By Miguel Osuna
  Modified: -/-/-
  By: -----------
*/

const int buttonPin = 7;
const int buzzerPin = 6;
int freq;

void setup()
{
    // Define the inputs and outputs
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(buzzerPin, OUTPUT);
    
    // Begin serial communication
    Serial.begin(9600);
    Serial.println("Please enter a frequency for you buzzer in Hz: ");
    freq = Serial.read();  
}

void loop()
{
    // Read the buttons state ('1' for floating value)
    int buttonState = digitalRead(buttonPin);

    // 'LOW' when the button is pressed
    if(buttonState == LOW)
        tone(buzzerPin, freq);
    else
        noTone(buzzerPin);
}

