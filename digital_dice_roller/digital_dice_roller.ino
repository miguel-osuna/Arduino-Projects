/*
  Digital Dice Roller
    
  This program displays a number entered by the user, from 0 to F (15) in hexadecimal on the 7-segment display

  Push-Button Asigned to Pin 1
  7-Segment Display 'a' pin Asigned to Pin 2
  7-Segment Display 'b' pin Asigned to Pin 3
  7-Segment Display 'c' pin Asigned to Pin 4
  7-Segment Display 'd' pin Asigned to Pin 5
  7-Segment Display 'e' pin Asigned to Pin 6
  7-Segment Display 'f' pin Asigned to Pin 7
  7-Segment Display 'g' pin Asigned to Pin 8
  7-Segment Display '.' pin Asigned to Pin 9

  The circuit:  
  1 7-Segment Display Common Anode or Common Cathode
  8 Resistors
  1 Push-Button

  Created 11/3/19
  By Miguel Osuna
  Modified: -/-/-
  By: -----------
*/

const int buttonPin = 1;
int sevenSegmentDisplayPins[] = {2, 3, 4, 5, 6, 7, 8};

//                     a, b, c, d, e, f, g, . 
byte digits[6][8] = 
{
                      {0, 1, 1, 0, 0, 0, 0, 0}, //1
                      {1, 1, 0, 1, 1, 0, 1, 0}, //2
                      {1, 1, 1, 1, 0, 0, 1, 0}, //3
                      {0, 1, 1, 0, 0, 1, 1, 0}, //4
                      {1, 0, 1, 1, 0, 1, 1, 0}, //5
                      {1, 0, 1, 1, 1, 1, 1, 0}, //6
};

byte spinDigits[6][8] =
{
                      {1, 0, 0, 0, 0, 0, 0 ,0},
                      {0, 1, 0, 0, 0, 0, 0, 0},
                      {0, 0, 1, 0, 0, 0, 0, 0},
                      {0, 0, 0, 1, 0, 0, 0, 0},
                      {0, 0, 0, 0, 1, 0, 0, 0},
                      {0, 0, 0, 0, 0, 1, 0, 0},
};

void setup()
{
    for(int i = 0; i < 8; i++)
    {
        pinMode(sevenSegmentDisplayPins[i], OUTPUT);
        digitalWrite(sevenSegmentDisplayPins[i], LOW);
    }
    pinMode(buttonPin, INPUT_PULLUP);
}

void loop()
{

  // Wait for the push-button to be pressed
  // We espect a LOW, because of the Internal Pull-up resistor
  if(digitalRead(buttonPin) == LOW)
  {
    spin();
    rollDice();
    delay(500);
  }
  
}

void numberToDisplay(int number)
{
    for(int i = 0; i < 8; i++)
        digitalWrite(sevenSegmentDisplayPins[i], digits[number-1][i]);
}

void rollDice()
{
    numberToDisplay(random(1,7));
}

void spin() 
{
  for (int j = 0; j < 6; j++) 
  {
      for (int i = 0; i < 8; i++) 
          digitalWrite(sevenSegmentDisplayPins[i], spinDigits[j][i]);
      delay(250);
  }
}
