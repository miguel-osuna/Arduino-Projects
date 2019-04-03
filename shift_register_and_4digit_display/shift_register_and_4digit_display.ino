/*
  Display Number on 4-digit Seven Segment Display
    
  This program displays a number entered by the user, from 0000 to 9999 in on the 4-digit 7-segment display
  
  7-Segment Display 'a' pin (11) Asigned to 74HC595 Pin 15 (Q0) This will be the last LED to turn on
  7-Segment Display 'b' pin (7) Asigned to 74HC595 Pin 1 (Q1)
  7-Segment Display 'c' pin (4) Asigned to 74HC595 Pin 2 (Q2)
  7-Segment Display 'd' pin (2) Asigned to 74HC595 Pin 3 (Q3)
  7-Segment Display 'e' pin (1) Asigned to 74HC595 Pin 4 (Q4)
  7-Segment Display 'f' pin (10) Asigned to 74HC595 Pin 5 (Q5)
  7-Segment Display 'g' pin (5) Asigned to 74HC595 Pin 6 (Q6)
  7-Segment Display '.' pin (3) Asigned to 74HC595 Pin 7 (Q7)

  74HC959 Data Pin (Pin 14) Asigned to Pin 4 of the Arduino
  74HC595 Latch Pin (Pin 12) Asigned to Pin 5 of the Arduino
  74HC595 Clock Pin (Pin 11) Asigned to Pin 6 of the Arduino

  Digit 1 Enable pin (12) Asigned to Pin 10
  Digit 2 Enable pin (9)  Asigned to Pin 11
  Digit 3 Enable pin (8)  Asigned to Pin 12
  Digit 4 Enable pin (6)  Asigned to Pin 13

  The circuit:  
  1 4-digit 7-Segment Display Common Anode or Common Cathode
  8 220 Ohm Resistors
  1 Shift Register (74HC595)

  Created 26/3/19
  By Miguel Osuna
  Modified: -/-/-
  By: -----------
*/

// We define all of the Shift Register - 74HC595 Pins
const int dataPin = 4;
const int latchPin = 5;
const int clockPin = 6;

const int sevenSegmentDisplayPins[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const int digitPins[4] = {10, 11, 12, 13};

//                     a, b, c, d, e, f, g, . 
const byte digits[10][8] = 
{
                      {1, 1, 1, 1, 1, 1, 0, 0}, //0
                      {0, 1, 1, 0, 0, 0, 0, 0}, //1
                      {1, 1, 0, 1, 1, 0, 1, 0}, //2
                      {1, 1, 1, 1, 0, 0, 1, 0}, //3
                      {0, 1, 1, 0, 0, 1, 1, 0}, //4
                      {1, 0, 1, 1, 1, 1, 1, 0}, //6
                      {1, 1, 1, 0, 0, 0, 0, 0}, //7
                      {1, 1, 1, 1, 1, 1, 1, 0}, //8
                      {1, 1, 1, 0, 0, 1, 1, 0}, //9
};

int displayNumbers[4] = {0};

// These 'byte' variables are to store the bits in the digits array in an array of 'single bytes'
byte numberToDigit[10];
byte leds;

void setup()
{
    // We configure the digit Pins as OUTPUTS
    for(int i = 0; i < 4; i++)
    {
        pinMode(digitPins[i], OUTPUT);
        digitalWrite(digitPins[i], LOW);
    }

    // We configure the necessary Pins for the Shift Register 
    pinMode(dataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);

    setDigitVals();

    Serial.begin(9600);
    Serial.setTimeout(20);
    Serial.print("Please enter a number between 0 and 9999 (with a 4 digit format): ");
}

void loop()
{
    // Wait for something in the Serial Port
    // Get the input from the user

    static String input;

    if(Serial.available())
    {
        // We read the users input as a string to then separate character by character 
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
    delay(2);

    //We set LOW to the output of the Second Digit and HIGH to all others
    digitalWrite(digitPins[0], !LOW);
    digitalWrite(digitPins[1], !HIGH);
    digitalWrite(digitPins[2], !LOW);
    digitalWrite(digitPins[3], !LOW);
    numberToDisplay(displayNumbers[1]);
    delay(2);

    //We set LOW to the output of the Third Digit and HIGH to all others
    digitalWrite(digitPins[0], !LOW);
    digitalWrite(digitPins[1], !LOW);
    digitalWrite(digitPins[2], !HIGH);
    digitalWrite(digitPins[3], !LOW);
    numberToDisplay(displayNumbers[2]);
    delay(2);
    
    //We set LOW to the output of the Fourth Digit and HIGH to all others
    digitalWrite(digitPins[0], !LOW);
    digitalWrite(digitPins[1], !LOW);
    digitalWrite(digitPins[2], !LOW);
    digitalWrite(digitPins[3], !HIGH);
    numberToDisplay(displayNumbers[3]);
    delay(2);
}

/* This function lets display a value to the 4-digit / 7-segment display */

void numberToDisplay(int number)
{
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, numberToDigit[number]);
    digitalWrite(latchPin, HIGH);
}

/* With this function, we go through the digits matrix in order
 * to generate the new numbers for the Shift Register
 */
void setDigitVals()
{
    for(int i = 0; i < 10; i++)
    {
        byte leds = 0;
        for(int j = 0; j < 8; j++)
        {
            /* The logic is for a Common Cathode 4-digit / 7-segment display
             * Otherwise, if your display is Common Anode, negate the bits of the 
             * 'numberToDigit' byte array

                In order to correctly represent the desired number, 
              * it is necessary to alter the order in which the bits are stored. 
              * The position of bit 0 will be changed, with that of bit 7.
              */
              
            if(digits[i][j] == 0)
                bitClear(leds, 7 - j);
            else
                bitSet(leds, 7 - j);
        }
        numberToDigit[i] = leds;
    }
}

// This function writes 0 to a digit
void clearDisplay()
{
    numberToDisplay(0);
}
