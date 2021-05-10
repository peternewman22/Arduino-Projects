const int joyX = A0;
const int joyY = A1;
const int joyS = 4;
int xValRaw;
int yValRaw;
int xVal;
int yVal;
int xOffset = 512-487;
int yOffset = 512-494;

void setup() {
  // put your setup code here, to run once:
  pinMode(joyS, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  xValRaw = analogRead(joyX) + xOffset;
  yValRaw = analogRead(joyY) + yOffset;
  xVal = map(xValRaw, 0, 1023, -512, 512);
  yVal = map(yValRaw, 0, 1023, -512, 512);
  Serial.print("("); 
  Serial.print(xValRaw);
  Serial.print(", ");
  Serial.print(yValRaw);
  Serial.print(")\t -->\t(");
  Serial.print(xVal);
  Serial.print(", ");
  Serial.print(yVal);
  Serial.println(")");
  delay(200);
  

}
