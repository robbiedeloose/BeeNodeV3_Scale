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
#define numberOfScales 3



void setup() {
  Serial.begin(9600);
  delay(5000);
  Serial.println("readings");
  pinMode(13, OUTPUT); 

  Serial.println(scale1.get_value(20));
  Serial.println(scale2.get_value(20));
  Serial.println(scale3.get_value(20));

  for(int i = 0;i<5;i++){
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);
    delay(50);
  }
  
  char buf[40];
  String results = String("<") + String(scale1.get_value(20),0) + "," + String(scale2.get_value(20),0) + "," + String(scale2.get_value(20),0) + ">" ;
  results.toCharArray(buf, 39);

  Serial.println(results);
  Serial.println(buf);
  
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event

}

void loop() {
  delay(100);
}

void requestEvent() {  
  char buf[51];
  String results = String("<") + String(scale1.get_value(20),0) + "," + String(scale2.get_value(20),0) + "," + String(scale2.get_value(20),0) + ">" ;
  results.toCharArray(buf, 51);
  for(int i = 0;i<5;i++){
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);
    delay(50);
  }
  Wire.write(buf); // respond with message of 6 bytes
  // as expected by master
}
