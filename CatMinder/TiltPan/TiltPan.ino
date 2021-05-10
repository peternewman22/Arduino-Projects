#include <Servo.h>

// declare constants
const int tiltPin = 5;
const int panPin = 6;
const int joyXPin = A0;
const int joyYPin = A3;
const int switchPin = 8;
const int printEvery = 500;
const int tiltMin = 10;
const int tiltLim = 135;
const int panMin = 10;
const int panLim = 170;
int joyX, joyY;
long currentTime;
long prevTime;
int tiltPos;
int panPos;
boolean manualMode;


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
  prevTime = 0;
  tiltPos = tiltMin;
  panPos = panMin;
  manualMode = true;
}



void loop() {
  // read the joyStick
  joyX = map(analogRead(joyXPin), 0, 1023, -512, 512);
  joyY = map(analogRead(joyYPin), 0, 1023, -512, 512);

  // print them out every printEvery milliseconds
  printJoystick();
  shiftByJoystick();

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
  switch(servo){
      case 0:
        tiltPos += dir;
        constrain(tiltPos, tiltMin, tiltLim);
        tilt.write(tiltPos);
        delay(15);
        break;
      case 1:
        panPos += dir;
        constrain(panPos, panMin, panLim);
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
