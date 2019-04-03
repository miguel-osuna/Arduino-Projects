/*
  DC Motor Speed Controller
    
  This program allows the user to control the speed and direction of a DC Motor With a Potentiometer and Push-button

  L293D Motor Driver Connections
  EN1 - Arduino 5V
  IN1 - Arduino Pin 7
  OUT1 - Motor Left Pin
  GND - Arduino GND
  GND - Arduino GND
  OUT2 - Arduino Right Pin
  IN2 - Arduino Pin 8
  Vs (Power Supply for Motor) - Vss (In this case, Arduino 5V)
  EN2 - NC
  IN3 - NC
  OUT3 - NC
  GND - Arduino GND
  GND - Arduino GND
  OUT4 - NC
  IN4 - NC
  Vss (Power Supply for IC) - Arduino 5V 

  Potentiometer Connections
  Pin 1 - GND
  Pin 2 - Arduino Pin A0
  Pin 3 - VCC

  Push-button Connections
  Pin 1 - GND
  Pin 2 - Arduino Pin 10

  The circuit:  
  1 L293D Motor Driver
  1 DC Motor
  1 10 KOhm Potentiometer
  1 Push-button

  Created 29/3/19
  By Miguel Osuna
  Modified: -/-/-
  By: -----------
*/

const int leftPin = 7;
const int rightPin = 8;
const int enablePin = 9; // PWM Pin to control motor speed

const int potPin = A0;
const int buttonPin = 10;

void setup()
{
    pinMode(leftPin, OUTPUT);
    pinMode(rightPin, OUTPUT);
    pinMode(enablePin, OUTPUT);
    pinMode(potPin, INPUT);
    pinMode(buttonPin, INPUT_PULLUP);

    Serial.begin(9600);
    stopMotor();
}

void loop()
{
    int motorSpeed = analogRead(potPin);
    motorSpeed = map(motorSpeed, 0, 1024, 0, 256);

    int buttonState = digitalRead(buttonPin);

    Serial.print("Speed: ");
    Serial.print(motorSpeed);
    Serial.print("  ");
    Serial.print("State: ");
    
    if(buttonState)
    {
        Serial.println("Forward");
        stopMotor();   
        forward(motorSpeed);
        delay(1000); 
    }
    
    else if(!buttonState)
    {
        Serial.println("Backward");
        stopMotor();
        backward(motorSpeed);
        delay(1000);
    }
}

void forward(int motorSpeed)
{
    analogWrite(enablePin, motorSpeed);
    digitalWrite(leftPin, HIGH);
    digitalWrite(rightPin, LOW); 
}

void backward(int motorSpeed)
{
    analogWrite(enablePin, motorSpeed);
    digitalWrite(leftPin, LOW);
    digitalWrite(rightPin, HIGH);
}

void stopMotor()
{
    digitalWrite(leftPin, LOW);
    digitalWrite(rightPin, LOW);
}

