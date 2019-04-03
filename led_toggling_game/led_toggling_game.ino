/*
  LED Toggling Game
      
  This program toggles various LEDs so the user can try to select when the Red LED Turns On
  
  Red LED Asigned to Pin 7
  Green LED Asigned to Pin 6
  Blue LED Asigned to Pin 5
  Push Button Asigned to Pin 2

  The circuit: 
  1 Red LED
  1 Green LED
  1 Blue LED
  1 Push-button

  Created 11/3/19
  By Miguel Osuna
  Modified: -/-/-
  By: -----------
*/

// Define all the pins used
const int redLed = 7;
const int greenLed = 6;
const int blueLed = 5;
const int pushButton = 2;

// Define the variables used
int timeOn[] = {100, 250, 400, 500};
int timeOff[] = {250, 500, 1000, 1500};

// Declaring the volatile variable so they can be access by the ISR
volatile bool isWinner = false;
volatile bool isToggled = false;

void setup()
{
    pinMode(redLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    pinMode(blueLed, OUTPUT);
    pinMode(pushButton, INPUT_PULLUP);        

    // We attach an interrupt to monitor the push button
    attachInterrupt(digitalPinToInterrupt(pushButton), checkToggle, FALLING);
    turnOffLeds();
}

void loop()
{
    int randomLed = random(1, 4);
    int duration = timeOn[random(1, 4)];
    ledToTurnOn(randomLed, duration);
    
    turnOffLeds();
    // Delay to make the game more unpredictable
    int delayTurnOff = timeOff[random(4)];
    delay(delayTurnOff);

    // Check if there is a winner
    if(isWinner == true)
    {
        // Reset the winning flag
        isWinner = false;
        gameWon();
    }
}

void ledToTurnOn(int led, int duration)
{
    switch(led)
    {
        // Red LED
        case 1:
            isToggled = true;            
            digitalWrite(redLed, HIGH);
            break;

        // Green LED
        case 2:
            digitalWrite(greenLed, HIGH);
            break;
            
        // Blue Led
        case 3:
            digitalWrite(blueLed, HIGH);
            break;
        
        // Any other case
        default:
            break;
    }
    // Time that has to be turned on
    delay(duration);

    // Reset toggle flag
    isToggled = false;
}

void turnOffLeds()
{
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);
    digitalWrite(blueLed, LOW);
}

void gameWon()
{
    for(int i = 0; i < 3; i++)
    {

        digitalWrite(redLed, HIGH);
        digitalWrite(greenLed, HIGH);
        digitalWrite(blueLed, HIGH);
        delay(200);
        digitalWrite(redLed, LOW);
        digitalWrite(greenLed, LOW);
        digitalWrite(blueLed, LOW);
        delay(200);
    }

    // Time until the next game starts
    delay(5000);
}

// ISR to determine if button was pressed in the correct moment
void checkToggle()
{
    if(isToggled == true)
        isWinner = true;
}

