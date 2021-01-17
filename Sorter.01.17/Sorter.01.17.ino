#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>

///////////// Servo /////////////
int directionalServo = 9;
int rotationalServo = 3;
int rServoSpeed = 89;
Servo dServo;
Servo rServo;

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

///////////// Setup /////////////
void setup() {
  dServo.attach(directionalServo);
  rServo.attach(rotationalServo);
  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
}

///////////// Loop /////////////
void loop() {
  rotateServo();
  float red, green, blue;

//  delay(60);  // takes 50ms to read -- With this commented, the sensor scans two values per bad bean
  tcs.getRGB(&red, &green, &blue);

  //  Serial.print("R:\t"); Serial.print(int(red));
  //  Serial.print("\tG:\t"); Serial.print(int(green));
  //  Serial.print("\tB:\t"); Serial.print(int(blue));

  if (red > 70 && blue <= 73) { //red > 75 && blue <= 75
    Serial.println("\n----------------Bad bean--------------------");
    Serial.print("R:\t"); Serial.print(int(red));
    Serial.print("\tG:\t"); Serial.print(int(green));
    Serial.print("\tB:\t"); Serial.print(int(blue));
    badBean();
    Serial.println("\n--------------------------------------------");
  } else {
    goodBean();
  }
}

void badBean() {
  dServo.write(0);
}

void goodBean() {
  dServo.write(90);
}

void rotateServo() {
  rServo.write(rServoSpeed);
}
