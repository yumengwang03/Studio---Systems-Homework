/*
  Software serial multple serial test
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
 * RX is digital pin 2 (connect to TX of xbee)
 * TX is digital pin 3 (connect to RX of xbee)
 */

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

const int potPin = A0;
int potVal = 0;

const char myName0[] = "Caio";
const char myName1[] = "Adam";
const char myName2[] = "Nico";
const char myName3[] = "Yumeng";

const char* const groupName[] = {myName0, myName1, myName2, myName3};

void setup()  
{
  Serial.begin(9600);

  mySerial.begin(9600);

//  Serial.println("Yumeng receving \n");
//
//  mySerial.println("Yumeng sending \n");
}

void loop() {
  potVal = analogRead(potPin);
  //Serial.println(potVal);

  serialCheck();
}

void serialCheck() {
  String buffer;

  if(Serial.available() > 0) {
    buffer = Serial.readStringUntil('\n');  
    if(buffer.startsWith(name, 0)) {
      mySerial.write(Serial.read());
    }
  }

  if (mySerial.available()) {
    Serial.write(mySerial.read());
    mySerial.print("Yumeng");
   // mySerial.print(potVal);
    mySerial.print('\n');
    // delay(100);
  }
}







