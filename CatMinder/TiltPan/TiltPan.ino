#include <FastLED.h>
#include <Servo.h>

// declare constants
const int tiltPin = 5;
const int panPin = 6;
const int joyXPin = A0;
const int joyYPin = A3;
const int switchPin = 8;
const int printEvery = 500;
const int tiltMin = 10;
const int tiltMax = 90;
const int panMin = 10;
const int panMax = 170;

// eye timing
const int eyeL = 2;
const int eyeR = 4;
boolean eyesOpen = true;
const int eyesOpenDuration = 10000;
const int eyesClosedDuration = 1000;

int joyX, joyY;
long currentTime;
long prevTime;
int tiltPos;
int panPos;
boolean manualMode;
float tiltNoiseValue;
float panNoiseValue;

// the noise variables
float tiltOffset = random(1000); //start with random seed
float panOffset = random(1000);
float tiltIncrement = 1;
float panIncrement = 5;
int noiseMin = 50;
int noiseMax = 190;
// declare Servos
Servo tilt;
Servo pan;

void setup() {
  Serial.begin(9600);
  tilt.attach(tiltPin);
  pan.attach(panPin);
  // Move the tilt through from 0 to 180
  sweep(tilt);
  sweep(pan);
  joyX = 0;
  joyY = 0;
  currentTime = 0;
  pinMode(eyeL,OUTPUT);
  pinMode(eyeR,OUTPUT);
  prevTime = 0;
  tiltPos = tiltMin;
  panPos = panMin;
  manualMode = false;
  tiltNoiseValue = inoise8(tiltOffset);
  tiltPos = constrain(map(tiltNoiseValue, noiseMin, noiseMax, tiltMin, tiltMax), tiltMin, tiltMax);
  panNoiseValue = inoise8(tiltOffset);
  panPos = constrain(map(panNoiseValue, noiseMin, noiseMax, panMin, panMax), panMin, panMax);
  digitalWrite(eyeL,HIGH);
  digitalWrite(eyeR,HIGH);
}


void loop() {
  // decide if in manualMode
  if (manualMode) {
    // read the joyStick
    joyX = map(analogRead(joyXPin), 0, 1023, -512, 512);
    joyY = map(analogRead(joyYPin), 0, 1023, -512, 512);

    // print them out every printEvery milliseconds
    printJoystick();
    shiftByJoystick();
  } else {
    tiltNoiseValue = inoise8(tiltOffset);
    tiltPos = constrain(map(tiltNoiseValue, noiseMin, noiseMax, tiltMin, tiltMax), tiltMin, tiltMax);
    panNoiseValue = inoise8(tiltOffset);
    panPos = constrain(map(panNoiseValue, noiseMin, noiseMax, panMin, panMax), panMin, panMax);
    tiltOffset += tiltIncrement;
    panOffset += panIncrement;
    pan.write(panPos);
    delay(15);
    tilt.write(tiltPos);
    delay(15);
//    printAutoData();
  }
}

void printAutoData(){
      Serial.print("TiltNoiseValue\t");
        Serial.print(tiltNoiseValue);
        Serial.print("...TiltPos:\t");
        Serial.print(tiltPos);
        Serial.print("...PanNoiseValue:\t");
        Serial.print(panNoiseValue);
        Serial.print("...PanPos:\t");
        Serial.println(panPos);
  }

void shiftByJoystick() {
  if (joyX == -512) {
    shiftServo(1, -1);
  }
  if (joyX == 512) {
    shiftServo(1, 1);
  }
  if (joyY == 512) {
    shiftServo(0, 1);
  }
  if (joyY == -512) {
    shiftServo(0, -1);
  }
}


void shiftServo(int servo, int dir) {
  switch (servo) {
    case 0:
      tiltPos += dir;
      constrain(tiltPos, tiltMin, tiltMax);
      tilt.write(tiltPos);
      delay(15);
      break;
    case 1:
      panPos += dir;
      constrain(panPos, panMin, panMax);
      pan.write(panPos);
      delay(15);
      break;
  }

}




void printJoystick() {
  // prints joystick data to the serial port every printEvery milliseconds
  currentTime = millis();
  if (currentTime - prevTime > printEvery) {
    Serial.print("joyX:\t");
    Serial.print(joyX);
    Serial.print("\tjoyY:\t");
    Serial.println(joyY);
    prevTime = currentTime;
  }
}

void sweep(Servo s) {
  // sweep servos back and forth through the full range of motion
  s.write(0);
  delay(500);
  for (int pos = 0; pos < 180; pos ++) {
    s.write(pos);
    delay(15);
  }
  for (int pos = 180; pos >= 0; pos --) {
    s.write(pos);
    delay(15);
  }
}
