// L FORWARD: digitalWrite(2,HIGH);
// L BACKWARD: analogWrite(5,100);
// R FORWARD: digitalWrite(4,HIGH);
// R BACKWARD: analogWrite(6,100);

void setup(){
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop(){
  analogWrite(6,50);
  analogWrite(5,50);
  //delay(2000);
}