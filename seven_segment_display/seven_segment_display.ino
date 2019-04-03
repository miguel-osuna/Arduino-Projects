/*
  Display Number on Seven Segment Display
    
  This program displays a number entered by the user, from 0 to F (15) in hexadecimal on the 7-segment display

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

  Created 11/3/19
  By Miguel Osuna
  Modified: -/-/-
  By: -----------
*/

int sevenSegmentDisplayPins[8] = {2, 3, 4, 5, 6, 7, 8, 9};

//                     a, b, c, d, e, f, g, . 
byte digits[16][8] = 
{
                      {1, 1, 1, 1, 1, 1, 0, 0}, //0
                      {0, 1, 1, 0, 0, 0, 0, 0}, //1
                      {1, 1, 0, 1, 1, 0, 1, 0}, //2
                      {1, 1, 1, 1, 0, 0, 1, 0}, //3
                      {0, 1, 1, 0, 0, 1, 1, 0}, //4
                      {1, 0, 1, 1, 0, 1, 1, 0}, //5
                      {1, 0, 1, 1, 1, 1, 1, 0}, //6
                      {1, 1, 1, 0, 0, 0, 0, 0}, //7
                      {1, 1, 1, 1, 1, 1, 1, 0}, //8
                      {1, 1, 1, 0, 0, 1, 1, 0}, //9
                      {1, 1, 1, 0, 1, 1, 1, 0}, //A (10)
                      {0, 0, 1, 1, 1, 1, 1, 0}, //B (11)
                      {1, 0, 0, 1, 1, 1, 0, 0}, //C (12)
                      {0, 1, 1, 1, 1, 0, 1, 0}, //D (13)
                      {1, 0, 0, 1, 1, 1, 1, 0}, //E (14)
                      {1, 0, 0, 0, 1, 1, 1, 0}  //F (15)
};                   

void setup()
{
    for(int i = 0; i < 8; i++)
    {
        pinMode(sevenSegmentDisplayPins[i], OUTPUT);
        digitalWrite(sevenSegmentDisplayPins[i], LOW);
    }
        
    Serial.begin(9600);
    Serial.print("Please enter a number between 0 and F (hexadecimal): ");
}

void loop()
{

  // Wait for something in the Serial Port
  // Get the input from the user
  if (Serial.available()) 
  {
      char ch = Serial.read();
      if (ch >= '0' && ch <= 'F') 
      {
          int number = ch - '0';
          if(number > 10)
              number -= 7;
          
          clearDisplay();
          numberToDisplay(number);
      }
  }
  else
      Serial.println("Please, enter another number: ");
}

void numberToDisplay(int number)
{
    for(int i = 0; i < 8; i++)
        digitalWrite(sevenSegmentDisplayPins[i], digits[number][i]);
}

void clearDisplay()
{
    for(int i = 0; i < 8; i++)
        digitalWrite(sevenSegmentDisplayPins[i], LOW);
}
