void setup(){
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop(){
  digitalWrite(4,HIGH);
  analogWrite(5,100);
  digitalWrite(2,HIGH);
  analogWrite(9,100);
  delay(2000);
  digitalWrite(4,LOW);
  analogWrite(5,100);
  digitalWrite(2,LOW);
  analogWrite(9,100);
  delay(2000);
  digitalWrite(4,LOW);
  analogWrite(5,100);
  digitalWrite(2,HIGH);
  analogWrite(9,100);
  delay(2000);
  digitalWrite(4,HIGH);
  analogWrite(5,100);
  digitalWrite(2,LOW);
  analogWrite(9,100);
  delay(2000);
  analogWrite(5,0);
  analogWrite(9,0);
  delay(2000);
}