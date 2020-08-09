// Has a relay (default closed) and opens under conditions of the moisture sensor

int sensorPin = A0;
//int relayPin = 2;
int moistureVal = 0;
int threshold = 400;
int interval = 1000;
void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin, INPUT);
//  pinMode(relayPin, OUTPUT);
  Serial.begin(9600); //init the console writing
}

void loop() {
  // put your main code here, to run repeatedly:
  //Reading the sensorPin
  
  moistureVal = analogRead(sensorPin);
  Serial.println(moistureVal);
 
//  if(moistureVal < threshold){
//    digitalWrite(relayPin, HIGH);
//    } else {
//      digitalWrite(relayPin, LOW);
//      };
  delay(interval);
  
}
