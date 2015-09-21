

#include <SoftwareSerial.h>

SoftwareSerial mySerial (2, 3);

const int buttonPin = 8;
const int greenLedPin = 5;
const int redLedPin = 6;
const int potPin = A0;

int potVal = 0;
int buttonState = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  
  pinMode(buttonPin, INPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
}

void loop() {
  //potentiometer
  potVal = analogRead(potPin);
  buttonState = analogRead(buttonPin);
  
  if (Serial.available()) {
    mySerial.write(Serial.read());
    if (Serial.readString() == "Yumeng") {
      for (int fadeValue = 0; fadeValue <= 255; fadeValue +=5) {
        analogWrite(redLedPin, fadeValue);
        delay(30);
      }
    }
  }
  
//  if (buttonState == LOW) {
//    Serial.println("button pressed");
    if (mySerial.available()) {
      Serial.write(mySerial.read());
      mySerial.print("Nico ");
      mySerial.print(potVal);
      mySerial.print("\n");
      
      analogWrite(greenLedPin, HIGH);
      delay(500);
      analogWrite(greenLedPin, LOW);
    }
//  } 
  
}


