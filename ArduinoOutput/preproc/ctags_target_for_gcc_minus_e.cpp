# 1 "c:\\Users\\15862\\Documents\\GitHub\\CoffeeSorter\\Sorter\\Sorter.ino"
# 2 "c:\\Users\\15862\\Documents\\GitHub\\CoffeeSorter\\Sorter\\Sorter.ino" 2

int rotationalServoPin = 3;
int rotationalServoCurrentSensorPin = A0;
int rotationalServoCurrentThreshold = 575;
int rotationalServoSensorValue;
int rotationalServoSpeed = 89;
Servo rotationalServo;

int reverseServoButtonPin = 2;
int buttonState = 0;

void setup(){
  rotationalServo.attach(rotationalServoPin);
  Serial.begin(9600);
  pinMode(reverseServoButtonPin, 0x0);
}

void loop(){
  buttonState = digitalRead(reverseServoButtonPin);
  Serial.println(buttonState);
  if (buttonState == 0x1) {
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
