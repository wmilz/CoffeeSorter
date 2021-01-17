#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h> 
#include <Stepper.h>

///////////// RGB LED /////////////
#define redpin 3
#define greenpin 5
#define bluepin 6
#define commonAnode false

///////////// Gamma Table /////////////
// our RGB -> eye-recognized gamma color
byte gammatable[256];


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

  // use these three pins to drive an LED
  #if defined(ARDUINO_ARCH_ESP32)
    ledcAttachPin(redpin, 1);
    ledcSetup(1, 12000, 8);
    ledcAttachPin(greenpin, 2);
    ledcSetup(2, 12000, 8);
    ledcAttachPin(bluepin, 3);
    ledcSetup(3, 12000, 8);
  #else
    pinMode(redpin, OUTPUT);
    pinMode(greenpin, OUTPUT);
    pinMode(bluepin, OUTPUT);
  #endif

  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;

    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;
    }
  }
}

///////////// Loop /////////////
void loop() {
  rotateServo();
  float red, green, blue;

  delay(60);  // takes 50ms to read
  rotateServo();
  tcs.getRGB(&red, &green, &blue);
  
//  Serial.print("R:\t"); Serial.print(int(red)); 
//  Serial.print("\tG:\t"); Serial.print(int(green)); 
//  Serial.print("\tB:\t"); Serial.print(int(blue)); 

  if (red > 70 && blue <= 73){ //red > 75 && blue <= 75
    Serial.println("\n----------------Bad bean--------------------");
    Serial.print("R:\t"); Serial.print(int(red)); 
    Serial.print("\tG:\t"); Serial.print(int(green)); 
    Serial.print("\tB:\t"); Serial.print(int(blue)); 
    badBean();
    Serial.println("\n--------------------------------------------");
  }else{
    goodBean();
  }
}

void badBean(){
  dServo.write(0);
}

void goodBean(){
  dServo.write(90);
}

void rotateServo(){
  rServo.write(rServoSpeed);
}
