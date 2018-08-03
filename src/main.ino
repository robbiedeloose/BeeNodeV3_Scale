/*
BeeLogV3 scale module
seperat arduino module that reads 6 HX711 scale modules.
You can request the scale data over i2C
will return 2 sets of data in <xxxxxxx,xxxxxxx,xxxxxxx> format. This is done because of the buffer limitaion on avr chip
*/

#include "arduino.h"
#include "HX711.h"


#define SCALE_1_DATA 2 // blauw
#define SCALE_1_CLOCK 3 // geel
#define SCALE_2_DATA 4 // blauw
#define SCALE_2_CLOCK 5 // geel
#define SCALE_3_DATA 6 // blauw
#define SCALE_3_CLOCK 7 // geel
#define SCALE_4_DATA 8 // blauw
#define SCALE_4_CLOCK 9 // geel
#define SCALE_5_DATA 10 // blauw
#define SCALE_5_CLOCK 11 // geel
#define SCALE_6_DATA 12 // blauw
#define SCALE_6_CLOCK 13 // geel

HX711 scale1(SCALE_1_DATA, SCALE_1_CLOCK);	// DT, SCK	// parameter "gain" is ommited; the default value 128 is used by the library
HX711 scale2(SCALE_2_DATA, SCALE_2_CLOCK);	// DT, SCK	// parameter "gain" is ommited; the default value 128 is used by the library
HX711 scale3(SCALE_3_DATA, SCALE_3_CLOCK);	// DT, SCK	// parameter "gain" is ommited; the default value 128 is used by the library
HX711 scale4(SCALE_4_DATA, SCALE_4_CLOCK);	// DT, SCK	// parameter "gain" is ommited; the default value 128 is used by the library
HX711 scale5(SCALE_5_DATA, SCALE_5_CLOCK);	// DT, SCK	// parameter "gain" is ommited; the default value 128 is used by the library
HX711 scale6(SCALE_6_DATA, SCALE_6_CLOCK);	// DT, SCK	// parameter "gain" is ommited; the default value 128 is used by the library

#include <Wire.h>

double readings[6];
#define numberOfScales 6
#define bufferSize 26
char buf1[bufferSize];
char buf2[bufferSize];

uint8_t requestCounter = 1;

void setup() {
  Serial.begin(9600);
  delay(250);
  Serial.println("readings");
  pinMode(13, OUTPUT);

  Serial.println(scale1.get_value(20));
  Serial.println(scale2.get_value(20));
  Serial.println(scale3.get_value(20));

  String results1 = String("<") + String(scale1.get_value(20),0) + "," + String(scale2.get_value(20),0) + "," + String(scale2.get_value(20),0) + ">" ;
  Serial.print("String (");
  Serial.print(results1.length());
  Serial.print(") : ");
  Serial.println(results1);

  String results2 = String("<") + String(scale4.get_value(20),0) + "," + String(scale5.get_value(20),0) + "," + String(scale6.get_value(20),0) + ">" ;
  Serial.print("String (");
  Serial.print(results2.length());
  Serial.print(") : ");
  Serial.println(results2);

  results1.toCharArray(buf1, bufferSize);
  Serial.print("Buf1: ");
  for(int i=0;i<bufferSize;i++){
    Serial.print(buf1[i]);
  }
  Serial.println();

  results2.toCharArray(buf2, bufferSize);
  Serial.print("Buf2: ");
  for(int i=0;i<bufferSize;i++){
    Serial.print(buf1[i]);
  }
  Serial.println();

  for(int i = 0;i<5;i++){
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);
    delay(50);
  }
  Wire.begin(1);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  delay(100);
}

void requestEvent() {
  switch (requestCounter) {
    case 1:
      Serial.println("request 1 recieved");
      Wire.write(buf1);
      ++requestCounter;
      break;
    case 2:
      Serial.println("request 2 recieved");
      Wire.write(buf2);
      ++requestCounter;
      break;
  }
  if (requestCounter > 2)
    requestCounter = 1;
    for(int i = 0;i<2;i++){
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      delay(50);
    }
}
