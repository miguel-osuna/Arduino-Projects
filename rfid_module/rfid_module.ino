/*
  Radio Frequency Identification Test  

  RF Transceiver Pins
  SDA Pin - Arduino Pin 10
  SCK - Arduino Pin 13
  MOSI - Arduino Pin 11
  MISO - Arduino Pin 12
  IRQ - NC
  GND - Arduino GND Pin
  RST - Arduino Pin 9
  3.3V - Arduino 3.3V Pin

  The circuit:  
  1 RF Transceiver
  1 RFID

  Created 29/3/19
  By Miguel Osuna
  Modified: 5/4/2019
  By: -----------
*/

#include <SPI.h>
#include <MFRC522.h>

const int ssPin = 10;
const int rstPin = 9;

// We define a MFRC522 class object
MFRC522 mfrc522(ssPin, rstPin);

void setup()
{
    // Setup everything
    Serial.begin(9600);
    SPI.begin();
    mfrc522.PCD_Init();
    Serial.println("Approximate your card to the reader...");
    Serial.println();
    
}

void loop()
{
    // Look for a new card
    if(!mfrc522.PICC_IsNewCardPresent())
        return;

    // Select one of the cards
    if(!mfrc522.PICC_ReadCardSerial())
        return;
    
    // Show UID on serial monitor
    Serial.print("UID tag: ");
    String content = "";
    byte letter;

    for(byte i = 0; i < mfrc522.uid.size; i++)
    {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }

    Serial.println();
    Serial.print("Message: ");
    content.toUpperCase();

    // Change here the UID of the card/keychain that you want to give access
    if(content.substring(1) == "D0 BD 68 25")
    {
        Serial.println("Authorized access");
        Serial.println();
        delay(3000);
    }

    else
    {
        Serial.println("Access denied");
        delay(3000);
    }
}

