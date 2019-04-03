/*
  Joystick LED Matrix Operation
    
  This program displays on a LED Matrix the Movement of a Joystick

  Joystick Connections
  GND - Arduino GND
  +5V - Arduino Vcc (5V)
  VRx - A1
  VRy - A0
  SW - A2

  LED Matrix Connections
  Vcc - Arduino Vcc (5V)
  GND - Arduino GNF
  DIN (Data In) - MOSI (Master Out Slave In) / Pin 11
  CS (Chip Select) - Slave Select / Pin 10
  CLK (Clock) - Serial Clock / Pin 13

  The circuit:  
  1 Joystick
  1 LED Matrix

  Created 21/3/19
  By Miguel Osuna
  Modified: -/-/-
  By: -----------
*/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

//First we define the pins used

//Joystick Pins
const int verticalAxis = A0;
const int horizontalAxis = A1;
const int selectButton = A2; //Used as digital 

//LED Matrix Pins
const int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK
//LED Matrix coordinates
int matrix_x, matrix_y;
//LED Matrix Object
const int numberHorizontalDisplays = 1;
const int numberVerticalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberHorizontalDisplays, numberVerticalDisplays);

// This sketch outputs serial data at 9600 baud rate (open Serial Monitor to view).

void setup()
{
    //Just for being clear, we specify the pin modes
    pinMode(verticalAxis, INPUT);
    pinMode(horizontalAxis, INPUT);
    pinMode(selectButton, INPUT_PULLUP);

    //Configure the LED Matrix Intensity
    matrix.setIntensity(5);
    
    Serial.begin(115200);
}

void loop()
{
    //We read the values of the potentiometer
    int horizontalValue = analogRead(horizontalAxis);
    int verticalValue = analogRead(verticalAxis);
    int select = digitalRead(selectButton);

    //We map the joystick values to the LED Matrix dimensions
    //We want the center dot to be the origin
    //The origin of the LED Matrix is in its top left corner, and it's 0,0
    //The end of the LED Matrix is at 7,7, on the bottom right corner
    matrix_x = map(verticalValue, 5, 1018, 0, 7);
    matrix_y = map(horizontalValue, 1018, 5, 0, 7);


    matrix.fillScreen(0);   //Clear the screen
    //display new x and y values
    Serial.print("x: ");
    Serial.print(matrix_x);
    Serial.print("  ");
    Serial.print("y: ");
    Serial.print(matrix_y);
    Serial.print("  ");

    //Turns-On the LEDs
    matrix.drawPixel(matrix_x, matrix_y, HIGH);
    matrix.write();   //Send bitmap to display
    delay(10);
    
    //We display the read values
    Serial.print("X-axis position: ");
    Serial.print(horizontalValue, DEC);
    Serial.print("  ");
    Serial.print("Y-axis position: ");
    Serial.print(verticalValue, DEC);
    Serial.print("  ");
    
    Serial.print("Button ");
    if(select == HIGH)
        Serial.println("not pressed");
    else
        Serial.println("pressed");
}

