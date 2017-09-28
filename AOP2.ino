#include <Console.h>
#include <Servo.h>//loading
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
 
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *leftMotor2 = AFMS.getMotor(2);
Adafruit_DCMotor *rightMotor1 = AFMS.getMotor(4);
Adafruit_DCMotor *rightMotor2 = AFMS.getMotor(3);

Servo pointer;

int servoDelay = 20;//bigger for slower
int motorDelay = 800;

unsigned long sensorValue;
const int servoPin = 9;
const int trigPin = 2;
const int echoPin = 3;
const int ButtonPin = 5;
const int ledPin = 13;
int shortDis = 1500;
int spd = 100;
int fast = 230;
int slow = 100;
int left;
int right;
int incomingByte;  

int lt = 20;
int rt = 160;
//0~180
bool running = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  AFMS.begin();
  Bridge.begin();
  Console.begin(); 

  while (!Console){
    ; // wait for Console port to connect.
  }
  Console.println("You're connected to the Console!!!!");
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);

  leftMotor1->run(FORWARD);
  leftMotor2->run(FORWARD);
  rightMotor1->run(FORWARD);
  rightMotor2->run(FORWARD);
  pointer.attach(servoPin);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  pinMode(ButtonPin, INPUT);
  pointer.write(90);
}

long Sonar(){
  unsigned long duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH,10000);
  return duration;
}

void loop() {
  if (Console.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Console.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'H') {
      digitalWrite(ledPin, HIGH);
    } 
    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == 'L') {
      digitalWrite(ledPin, LOW);
    }
  }
  delay(100);
  /*potReading = analogRead(potPin);
  pos = (178./1023.)*potReading+2;*/
  if(running){
    for(int i=lt;i<=rt;i+=10){
      pointer.write(i);
      sensorValue = (int)Sonar();
      Serial.println(sensorValue);
      if (sensorValue<shortDis&&sensorValue>0){
        leftMotor1->run(BACKWARD);
        leftMotor2->run(BACKWARD);
        rightMotor1->run(BACKWARD);
        rightMotor2->run(BACKWARD);
        if(i<=120){
          left = slow;
          right = fast;
        }
        else{
          left = fast;
          right = slow;
        }
        while (sensorValue<shortDis&&sensorValue>0){
          leftMotor1->setSpeed(left);
          leftMotor2->setSpeed(left);
          rightMotor1->setSpeed(right);
          rightMotor2->setSpeed(right);
          sensorValue = (int)Sonar();
          Serial.println(sensorValue);
          delay(motorDelay);
        }  
      }
      else{
        leftMotor1->run(FORWARD);
        leftMotor2->run(FORWARD);
        rightMotor1->run(FORWARD);
        rightMotor2->run(FORWARD);
  
        leftMotor1->setSpeed(spd);
        leftMotor2->setSpeed(spd);
        rightMotor1->setSpeed(spd);
        rightMotor2->setSpeed(spd);
      }
      delay(servoDelay);
    }
    for(int i=rt;i>lt;i-=10){
      pointer.write(i);
      sensorValue = (int)Sonar();
      Serial.println(sensorValue);
      if (sensorValue<shortDis&&sensorValue>0){
        leftMotor1->run(BACKWARD);
        leftMotor2->run(BACKWARD);
        rightMotor1->run(BACKWARD);
        rightMotor2->run(BACKWARD);
        if(i<=120){
          left = slow;
          right = fast;
        }
        else{
          left = fast;
          right = slow;
        }
        while (sensorValue<shortDis&&sensorValue>0){
          leftMotor1->setSpeed(left);
          leftMotor2->setSpeed(left);
          rightMotor1->setSpeed(right);
          rightMotor2->setSpeed(right);
          sensorValue = (int)Sonar();
          Serial.println(sensorValue);
          delay(motorDelay);
        }  
      }
      else{
        leftMotor1->run(FORWARD);
        leftMotor2->run(FORWARD);
        rightMotor1->run(FORWARD);
        rightMotor2->run(FORWARD);
  
        leftMotor1->setSpeed(spd);
        leftMotor2->setSpeed(spd);
        rightMotor1->setSpeed(spd);
        rightMotor2->setSpeed(spd);
      }
      delay(servoDelay);
    }
  }
  else{
    leftMotor1->setSpeed(0);
    leftMotor2->setSpeed(0);
    rightMotor1->setSpeed(0);
    rightMotor2->setSpeed(0);
  }
}


