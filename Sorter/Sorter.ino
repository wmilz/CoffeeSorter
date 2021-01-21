#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>

///////////// Servo /////////////
int directionalServo = 9;
int rotationalServo = 3;

//int rServoSpeed = 89;
int rServoSpeed = 89;
Servo dServo;
Servo rServo;

String state = "good";

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

////RGB Mins/Maxes
//float redMin = 68; //worked well
//float redMax = 73;
//float greenMin = 81.5;
//float greenMax = 95;
//float blueMin = 60;
//float blueMax = 74.5;

float redMin = 70;
float redMax = 73;
float greenMin = 82.8;
float greenMax = 255;
float blueMin = 73.6;
float blueMax = 76.4;

///////////// Internal Counters /////////////
float tempRed = 0.0;
float tempGreen = 0.0;
float tempBlue = 0.0;
float redAvg = 0.0;
float greenAvg = 0.0;
float blueAvg = 0.0;
int readCount = 0;

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
  directServo();
  float red, green, blue;

  delay(60);  // takes 50ms to read -- With this commented, the sensor scans two values per bad bean
  tcs.getRGB(&red, &green, &blue);

//    Serial.print("R:\t"); Serial.print(int(red));
//    Serial.print("\tG:\t"); Serial.print(int(green));
//    Serial.print("\tB:\t"); Serial.println(int(blue));
  directServo();

  if (((int(red) < 100)&&(int(green) > 90)&&(int(blue) < 190)) || ((int(red) >= 100)&&(int(green) > 98)&&(int(blue) > 85))){
    if (redAvg != 0 && greenAvg != 0 && blueAvg != 0){
      boolean beanIsBad = checkBean(redAvg, greenAvg, blueAvg);
      if (beanIsBad){
        badBean();
        printRGB(redAvg, greenAvg, blueAvg);
      }else{
        goodBean();
        printRGB(redAvg, greenAvg, blueAvg);
      }
    }
    resetCounters();
  }else{
    tempRed = tempRed + red;
    tempGreen = tempGreen + green;
    tempBlue = tempBlue + blue;
    readCount++;
    redAvg = tempRed/readCount;
    greenAvg = tempGreen/readCount;
    blueAvg = tempBlue/readCount;
  }
}

boolean checkBean(float red, float green, float blue){ //true is good bean, false is bad bean
//    Serial.println("bean scanned");
//    Serial.print("R:\t"); Serial.print((red));
//    Serial.print("\tG:\t"); Serial.print((green));
//    Serial.print("\tB:\t"); Serial.println((blue));
//    Serial.println("------------------------");
if (((red >= redMin && red <= redMax) && 
  (green >= greenMin && green <= greenMax) && 
  (blue <= 75))
  ||
  ((red >= 68 && red < 70)&&(blue  < 75.5))
  ||
  ((red < 68)&&(blue  < 75.8))){
    return true;
  }else{
    return false;
  }
}

void badBean() {
  state = "bad";
  directServo();
  delay(1000);
}

void goodBean() {
  state = "good";
  directServo();
}

void directServo()  {
  if (state == "bad"){
    dServo.write(90);
  } else if (state == "good"){
    dServo.write(150);
  }
}

void rotateServo() {
  rServo.write(rServoSpeed);
}

void printRGB(float red, float green, float blue){
  //    Serial.print("R:\t"); 
    Serial.print(red);
    Serial.print(",");
//    Serial.print("\tG:\t"); 
    Serial.print(green);
    Serial.print(",");
//    Serial.print("\tB:\t"); 
    Serial.print(blue);
    Serial.print(",");
    Serial.print(state);
    Serial.print(",");
    Serial.println();
}

void resetCounters(){
    if (tempRed != 0)
      tempRed = 0;
    if (tempGreen != 0)
      tempGreen = 0;
    if (tempBlue != 0)
      tempBlue = 0;
    if (redAvg != 0)
      redAvg = 0;
    if (greenAvg != 0)
      greenAvg = 0;
    if (blueAvg != 0)
      blueAvg = 0;
    if (readCount != 0)
      readCount = 0;
}
