/*
  Display Number on 4-digit Seven Segment Display
    
  This program displays a number entered by the user, from 0000 to 9999 in on the 4-digit 7-segment display

  7-Segment Display 'a' pin (11) Asigned to Pin 2
  7-Segment Display 'b' pin (7) Asigned to Pin 3
  7-Segment Display 'c' pin (4) Asigned to Pin 4
  7-Segment Display 'd' pin (2) Asigned to Pin 5
  7-Segment Display 'e' pin (1) Asigned to Pin 6
  7-Segment Display 'f' pin (10) Asigned to Pin 7
  7-Segment Display 'g' pin (5) Asigned to Pin 8
  7-Segment Display '.' pin (3) Asigned to Pin 9

  Digit 1 Enable pin (12) Asigned to Pin 10
  Digit 2 Enable pin (9)  Asigned to Pin 11
  Digit 3 Enable pin (8)  Asigned to Pin 12
  Digit 4 Enable pin (6)  Asigned to Pin 13

  The circuit:  
  1 4-digit 7-Segment Display Common Anode or Common Cathode
  8 Resistors

  Created 22/3/19
  By Miguel Osuna
  Modified: -/-/-
  By: -----------
*/

int sevenSegmentDisplayPins[8] = {2, 3, 4, 5, 6, 7, 8, 9};
int digitPins[4] = {10, 11, 12, 13};

//                     a, b, c, d, e, f, g, . 
byte digits[10][8] = 
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
};

int displayNumbers[4] = {0};

void setup()
{
    for(int i = 0; i < 8; i++)
    {
        pinMode(sevenSegmentDisplayPins[i], OUTPUT);
        digitalWrite(sevenSegmentDisplayPins[i], LOW);
    }

    for(int i = 0; i < 4; i++)
    {
        pinMode(digitPins[i], OUTPUT);
        digitalWrite(digitPins[i], LOW);
    }
        
    Serial.begin(9600);
    Serial.setTimeout(20);
    Serial.print("Please enter a number between 0000 and 9999 (with a 4 digit format): ");
}

void loop()
{
    // Wait for something in the Serial Port
    // Get the input from the user

    static String input;
    
    if (Serial.available()) 
    {
        //We read the users input as a string to then separate character by character 
        input = Serial.readString();
        Serial.println();
        
        //Converting numbers to integers
        for(int i = 0; i < 4; i++)
        {
            //Read input string and convert each character to a number to be added to the displayNumbers array
            displayNumbers[i] = input.charAt(i) - '0';
            Serial.print(displayNumbers[i]);
        }
        Serial.println();      
    }

    clearDisplay();
    updateDigits(displayNumbers);
}

void updateDigits(int displayNumbers[])
{
    //Because the Display is Common Cathode, we have to set with the opposite State
    //for each digit Pins
    
    //We set LOW to the output of the First Digit and HIGH to all others
    digitalWrite(digitPins[0], !HIGH);
    digitalWrite(digitPins[1], !LOW);
    digitalWrite(digitPins[2], !LOW);
    digitalWrite(digitPins[3], !LOW);
    numberToDisplay(displayNumbers[0]);
    delay(5);

    //We set LOW to the output of the Second Digit and HIGH to all others
    digitalWrite(digitPins[0], !LOW);
    digitalWrite(digitPins[1], !HIGH);
    digitalWrite(digitPins[2], !LOW);
    digitalWrite(digitPins[3], !LOW);
    numberToDisplay(displayNumbers[1]);
    delay(5);

    //We set LOW to the output of the Third Digit and HIGH to all others
    digitalWrite(digitPins[0], !LOW);
    digitalWrite(digitPins[1], !LOW);
    digitalWrite(digitPins[2], !HIGH);
    digitalWrite(digitPins[3], !LOW);
    numberToDisplay(displayNumbers[2]);
    delay(5);
    
    //We set LOW to the output of the Fourth Digit and HIGH to all others
    digitalWrite(digitPins[0], !LOW);
    digitalWrite(digitPins[1], !LOW);
    digitalWrite(digitPins[2], !LOW);
    digitalWrite(digitPins[3], !HIGH);
    numberToDisplay(displayNumbers[3]);
    delay(5);
}

void numberToDisplay(int number)
{
    for(int i = 0; i < 8; i++)
        // The display is Common Anode, so we turn on each LED with a HIGH state
        digitalWrite(sevenSegmentDisplayPins[i], digits[number][i]);
}

void clearDisplay()
{
    for(int i = 0; i < 8; i++)
        digitalWrite(sevenSegmentDisplayPins[i], LOW);
}
