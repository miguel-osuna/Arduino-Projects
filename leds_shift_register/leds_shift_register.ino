/*
  Turn-On LEDs by using a Shift Register
    
  This program turns on 8 LEDs by using the Parallel Output from a Shift Register,
  and controlling the LED's intensity

  74HC959 Data Pin (Pin 14) Asigned to Pin 4 of the Arduino
  74HC595 Latch Pin (Pin 12) Asigned to Pin 5 of the Arduino
  74HC595 Clock Pin (Pin 11) Asigned to Pin 6 of the Arduino
  74GC595 Output Enable Pin (Pin 13 - Negative) Asigned to Pin 3 of the Arduino
  
  LED 1 Asigned to 74HC595 Pin 15 (Q0) This will be the last LED to turn on
  LED 2 Asigned to 74HC595 Pin 1 (Q1)
  LED 3 Asigned to 74HC595 Pin 2 (Q2)
  LED 4 Asigned to 74HC595 Pin 3 (Q3)
  LED 5 Asigned to 74HC595 Pin 4 (Q4)
  LED 6 Asigned to 74HC595 Pin 5 (Q5)
  LED 7 Asigned to 74HC595 Pin 6 (Q6)
  LED 8 Asigned to 74HC595 Pin 7 (Q7)

  The circuit:  
  1 Shift Register (74HC595)
  8 Resistors
  8 LEDs

  Created 26/3/19
  By Miguel Osuna
  Modified: -/-/-
  By: -----------
*/

// We define all of the 74HC595 Pins
const int dataPin = 4;
const int latchPin = 5;
const int clockPin = 6;

// We use Pin 3 of the Arduino as a PWM
int outputEnablePin = 3;

byte led = 0;

void setup()
{
    pinMode(dataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(outputEnablePin, OUTPUT);
}

void loop()
{
    setBrightness(255);
    // We set all of the LEDs off, by giving the variable 'led' the value of 0
    led = 0;
    updateShiftRegister();
    delay(500);

    // Here we turn each LED one by one
    for(int i = 0; i < 8; i++)
    {
        // It sets each bit of the 'led' byte to 'HIGH' from the LSB to the MSB
        bitSet(led, i);
        updateShiftRegister();
        delay(250);
    }

    
    for(byte i = 255; i > 0; i--)
    {
        setBrightness(i);
        delay(25);
    }
}

void setBrightness(byte brightness)
{
    analogWrite(outputEnablePin, 255 - brightness);
}

/*This function sets the latchPin to 'LOW', the calls
 * the Arduino function 'shiftOut' to shift out the contents of the variable 'leds'
 * in the shift register before putting the latchPin 'HIGH' again.
 */
void updateShiftRegister()
{
    // In order to change the bit, the latch has to transition from 'LOW' state to 'HIGH'
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, led);
    digitalWrite(latchPin, HIGH);
}

