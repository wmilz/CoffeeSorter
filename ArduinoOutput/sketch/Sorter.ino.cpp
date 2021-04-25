#include <Arduino.h>
#line 1 "c:\\Users\\15862\\Documents\\GitHub\\CoffeeSorter\\Sorter\\Sorter.ino"
#include <Servo.h>

int rotationalServoPin = 3;
int rotationalServoCurrentSensorPin = A0;
int rotationalServoCurrentThreshold = 575;
int rotationalServoSensorValue;
int rotationalServoSpeed = 89;
Servo rotationalServo;

int reverseServoButtonPin = 2;
int buttonState = 0;

#line 13 "c:\\Users\\15862\\Documents\\GitHub\\CoffeeSorter\\Sorter\\Sorter.ino"
void setup();
#line 19 "c:\\Users\\15862\\Documents\\GitHub\\CoffeeSorter\\Sorter\\Sorter.ino"
void loop();
#line 29 "c:\\Users\\15862\\Documents\\GitHub\\CoffeeSorter\\Sorter\\Sorter.ino"
void rotateServo();
#line 33 "c:\\Users\\15862\\Documents\\GitHub\\CoffeeSorter\\Sorter\\Sorter.ino"
void reverseServo();
#line 13 "c:\\Users\\15862\\Documents\\GitHub\\CoffeeSorter\\Sorter\\Sorter.ino"
void setup(){
  rotationalServo.attach(rotationalServoPin);
  Serial.begin(9600);
  pinMode(reverseServoButtonPin, INPUT);
}

void loop(){
  buttonState = digitalRead(reverseServoButtonPin);
  Serial.println(buttonState);
  if (buttonState == HIGH) {
    reverseServo();
  }else{
    rotateServo();
  }
}

void rotateServo(){
  rotationalServo.write(rotationalServoSpeed);
}

void reverseServo(){
  rotationalServo.write(100);
}
