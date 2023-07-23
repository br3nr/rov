// L FORWARD: digitalWrite(2,HIGH);
// L BACKWARD: analogWrite(5,100);
// R FORWARD: digitalWrite(4,HIGH);
// R BACKWARD: analogWrite(6,100);

void setup(){
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(9, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop(){

  int switchState = digitalRead(9);
  
  if (switchState == HIGH) {
    Serial.println("Button is closed.");
    analogWrite(6,0);
    analogWrite(5,0);
  } else {
    Serial.println("Button is open.");
    analogWrite(6,50);
    analogWrite(5,50);
  }
  
  delay(100);
}