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

//HX711 scale2(4, 5);

double readings[6];
#define numberOfScales 3

void setup() {
  Serial.begin(9600);

  readings[0] = scale1.get_value(20);
  readings[1] = scale2.get_value(20);
  readings[2] = scale3.get_value(20);

  for (int i = 0; i<numberOfScales;i++)
  {
    Serial.print(readings[i],0);
    Serial.print(",");
  }
  Serial.println("#");
  delay(10000);
}

void loop() {

  readings[0] = scale1.get_value(20);
  readings[1] = scale2.get_value(20);
  readings[2] = scale3.get_value(20);

  for (int i = 0; i<numberOfScales;i++)
  {
    Serial.print("Scale ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(readings[i],0);
  }
  Serial.println();
  delay(1000);

}
