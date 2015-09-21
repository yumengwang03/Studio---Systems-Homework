/*
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
 * RX is digital pin 2 (connect to TX of xbee)
 * TX is digital pin 3 (connect to RX of xbee)
 */

#include <SoftwareSerial.h>

SoftwareSerial xbeeSerial(2, 3);  //RX, TX

const int buttonPin = 8; 
const int redLedPin = 6;  
const int greenLedPin = 5;  
const int potPin = A0; 

int potVal = 0;
int buttonState = 0;  

const char myName0[] = "Caio";
const char myName1[] = "Adam";
const char myName2[] = "Nico";
const char myName3[] = "Yumeng";

const char* const groupName[] = {
  myName0, myName1, myName2, myName3};

void setup() {
  Serial.begin(9600);
  Serial.println("Yumeng is broadcasting");

  xbeeSerial.begin(9600);

  pinMode(buttonPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
}

void loop(){
  broadcast();
  serialCheck();
}

void broadcast() {
  int buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {
    if (xbeeSerial.available()) {
      potVal = analogRead(potPin);
      //broadcasting the potentiometer value
      Serial.write(xbeeSerial.read());
      xbeeSerial.println(myName3 + potVal + '\n');
      digitalWrite(greenLedPin, HIGH);
      delay(500);
      digitalWrite(greenLedPin, LOW);
    }
  }
}

void serialCheck() {
  if (Serial.available()) {
    xbeeSerial.write(Serial.read());
    String buffer;
    //Serial.println("work!");
    buffer = xbeeSerial.readStringUntil('\n');  
    for (int i = 0; i < 4; i++) {
      if (buffer.startsWith(groupName[i], 0)) {
        Serial.println(buffer);
        int brightness = xbeeSerial.parseInt();
        digitalWrite(redLedPin, brightness);
        delay(500);
        digitalWrite(redLedPin, LOW);
      }
    }
  } 
}


