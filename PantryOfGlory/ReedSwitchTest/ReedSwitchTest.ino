// Declaring pins
const int REED_PIN = 2;
const int LED_PIN = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(REED_PIN, INPUT_PULLUP); //Pin connected to the reed switch
  pinMode(LED_PIN, OUTPUT); // LED pin - active-high
}

void loop() {
  // put your main code here, to run repeatedly:
  int closeness = digitalRead(REED_PIN); //Read the switch
  if (closeness == HIGH) 
  {
    Serial.println("Switch open i.e. door open");
    digitalWrite(LED_PIN, HIGH);
    } 
    else {
      digitalWrite(LED_PIN, LOW); // Turn the LED off  if the door is closed i.e. proximity LOW
    }
}
