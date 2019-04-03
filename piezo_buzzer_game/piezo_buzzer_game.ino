/*
  Piezo Buzzer Game
    
  This program plays a sequence of tones using buzzers and the user must recreate it using the corresponding push buttons.  
  
  Buzzer 1 Asigned to Pin 4
  Buzzer 2 Asigned to Pin 5
  Buzzer 3 Asigned to Pin 6
  Push-Button 1 Asigned to Pin 7
  Push-Buttton 2 Asigned to Pin 8
  Push-Button 3 Asigned to Pin 9

  The circuit: 
  3 LEDs
  3 Push-Buttons
  3 Piezo Buzzers

  Created 13/3/19
  By Miguel Osuna
  Modified: -/-/-
  By: -----------
*/

#include <Bounce2.h>

const int button1 = 7;
const int button2 = 8;
const int button3 = 9;

const int buzzer1 = 4;
const int buzzer2 = 5;
const int buzzer3 = 6;

// Initialize Bounce Objects
Bounce debouncer1 = Bounce();
Bounce debouncer2 = Bounce();
Bounce debouncer3 = Bounce();

int noteSequence[4];
int numNotes = sizeof(noteSequence[4]) / sizeof(int);
int currentNote = 0;
bool gameOn = true;

void setup()
{
    pinMode(button1, INPUT_PULLUP);
    pinMode(button2, INPUT_PULLUP);
    pinMode(button3, INPUT_PULLUP);

    pinMode(buzzer1, OUTPUT);
    pinMode(buzzer2, OUTPUT);
    pinMode(buzzer3, OUTPUT);

   // After setting up the buttons, setup the Bounce instances :
   debouncer1.attach(button1);
   debouncer1.interval(5); // Interval in ms
   debouncer2.attach(button2);
   debouncer2.interval(5); // Interval in ms
   debouncer3.attach(button3);
   debouncer3.interval(5); // Interval in ms

   // Generating a random number
   // As it where a floated Pin
   randomSeed(analogRead(0));
}

void loop()
{
    if(gameOn)
    {
        gameOn = false;
        currentNote = 0;
        playSequence(noteSequence);
    }

    debouncer1.update();
    debouncer2.update();
    debouncer3.update();

    int buttonValue1 = debouncer1.read();
    int buttonValue2 = debouncer2.read();
    int buttonValue3 = debouncer3.read();

    if( debouncer1.fell() )
    {
        playNote(1);
        verifyNotePlayed(1);
    }

    if( debouncer2.fell() )
    {
        playNote(2);
        verifyNotePlayed(2);
    }

    if( debouncer3.fell() )
    {
        playNote(3);
        verifyNotePlayed(3);
    }
}

void generateRandomSequence()
{
    for(int i = 0; i < numNotes; i++)
        noteSequence[i] = random(1, numNotes);
}

void playSequence(int notes[])
{
    for(int i = 0; i < numNotes; i++)
        playNote(notes[i]);
}

void playNote(int note)
{
    switch(note)
    {
        case 1:
            tone(buzzer1, 500);
            delay(500);
            noTone(buzzer1);
            delay(500);
            break;  

        case 2: 
            tone(buzzer2, 1000);
            delay(500);
            noTone(buzzer2);
            delay(500);
            break;

        case 3:
            tone(buzzer3, 1500);
            delay(500);
            noTone(buzzer2);
            delay(500);
            break;

        default:
            break;  
    }
}

void verifyNotePlayed(int note)
{
    if(currentNote < numNotes)
    {
        if(noteSequence[currentNote] == note)
        {
            currentNote++;
            if(currentNote == numNotes)
                winner();
        }

        else
            loser();
    }
}

void winner()
{
   currentNote = 0;
   gameOn = true;
   generateRandomSequence();
   for(int i = 0; i < 3; i++)
   {
      tone(buzzer3, 2000);
      delay(250);
      noTone(buzzer3);
      delay(250); 
   }
   delay(1000);
}

void loser()
{
    currentNote = 0;
    gameOn = true;
    tone(buzzer1, 5000);
    delay(250);
    noTone(buzzer1);
    delay(1000);
}

