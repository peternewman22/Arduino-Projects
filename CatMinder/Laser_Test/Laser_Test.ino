/*
  Laser Test

  Testing cycling three lasers at random intervals
*/

const int laser1 = 2;
const int laser2 = 3;
const int laser3 = 4;
long stateNumber = 0;
long randomNumber = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(laser1, OUTPUT);
  pinMode(laser2, OUTPUT);
  pinMode(laser3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 
  randomNumber = random(0,100);

  if (randomNumber < 10)
  {
    stateNumber = random(0,3);
    switchState();
  }
  delay(500);
  Serial.print("randomNumber: ");
  Serial.println(randomNumber);

}


void switchState() {
  Serial.print("Changing State to ");
  Serial.println(stateNumber);
  switch (stateNumber)
  {
    case 0:
      digitalWrite(laser1, HIGH);
      digitalWrite(laser2, LOW);
      digitalWrite(laser3, LOW);
      break;
    case 1:
      digitalWrite(laser1, LOW);
      digitalWrite(laser2, HIGH);
      digitalWrite(laser3, LOW);
      break;
    case 2:
      digitalWrite(laser1, LOW);
      digitalWrite(laser2, LOW);
      digitalWrite(laser3, HIGH);
      break;

  }
}
