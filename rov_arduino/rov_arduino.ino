#define IIC_SCL A5
#define IIC_SDA A4

unsigned char current_state = 0;  // 0: stopped, 1: forward, 2: left, 3: right
int speeds = 100;

// Your original display patterns
unsigned char images[4][16] = {
  { 0x00,0x08,0x08,0x00,0x00,0x30,0x30,0x08,0x08,0x30,0x30,0x00,0x00,0x08,0x08,0x00 },
  { 0x00,0x0C,0x0C,0x00,0x00,0x30,0x30,0x08,0x08,0x30,0x30,0x00,0x00,0x0C,0x0C,0x00 },
  { 0x00,0x0C,0x08,0x00,0x00,0x30,0x30,0x08,0x08,0x30,0x30,0x00,0x00,0x0C,0x08,0x00 },
  { 0x00,0x08,0x0C,0x00,0x00,0x30,0x30,0x08,0x08,0x30,0x30,0x00,0x00,0x08,0x0C,0x00 } 
};

void setup() {
  pinMode(IIC_SCL, OUTPUT);
  pinMode(IIC_SDA, OUTPUT);
  digitalWrite(IIC_SCL, LOW);
  digitalWrite(IIC_SDA, LOW);
  pinMode(4, OUTPUT);  // right motor control
  pinMode(2, OUTPUT);  // left motor control
  pinMode(1, INPUT_PULLUP);  // left button
  pinMode(9, INPUT_PULLUP);  // forward button
  pinMode(10, INPUT_PULLUP);  // right button
  Serial.begin(9600);
}

void loop() {
  int leftState = digitalRead(1);
  int forwardState = digitalRead(9);
  int rightState = digitalRead(10);
  
  Serial.print("Left: ");
  Serial.print(leftState);
  Serial.print(" Forward: ");
  Serial.print(forwardState);
  Serial.print(" Right: ");
  Serial.println(rightState);

  if (forwardState == LOW) {
    car_front();
    current_state = 1;
    updateDisplay();
  }
  else if (leftState == LOW) {
    car_left();
    current_state = 2;
    updateDisplay();
  }
  else if (rightState == LOW) {
    car_right();
    current_state = 3;
    updateDisplay();
  }
  else {
    car_Stop();
    current_state = 0;
    updateDisplay();
  }
  
  delay(10);
}

void car_front() {
  digitalWrite(2, LOW); 
  analogWrite(6, speeds);
  digitalWrite(4, LOW);
  analogWrite(5, speeds);
}

void car_left() {
  digitalWrite(2, HIGH); 
  analogWrite(6, (255 - speeds)); 
  digitalWrite(4, LOW);  
  analogWrite(5, speeds); 
}

void car_right() {
  digitalWrite(2, LOW);  
  analogWrite(6, speeds); 
  digitalWrite(4, HIGH);  
  analogWrite(5, (255 - speeds));
}

void car_Stop() {
  digitalWrite(2, LOW);
  analogWrite(6, 0);
  digitalWrite(4, LOW);
  analogWrite(5, 0);
}

void updateDisplay() {
  IIC_start();
  IIC_send(0x40);
  IIC_end();
  IIC_start();
  IIC_send(0xc0);
  for (char i = 0; i < 16; i++) {
    IIC_send(images[current_state][i]);
  }
  IIC_end();
  IIC_start();
  IIC_send(0x8A);
  IIC_end();
  delay(100);
}

void IIC_start() {
  digitalWrite(IIC_SCL, LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA, HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SCL, HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA, LOW);
  delayMicroseconds(3);
}

void IIC_send(unsigned char send_data) {
  for (char i = 0; i < 8; i++) {
    digitalWrite(IIC_SCL, LOW);
    delayMicroseconds(3);
    if (send_data & 0x01) {
      digitalWrite(IIC_SDA, HIGH);
    } else {
      digitalWrite(IIC_SDA, LOW);
    }
    delayMicroseconds(3);
    digitalWrite(IIC_SCL, HIGH);
    delayMicroseconds(3);
    send_data = send_data >> 1;
  }
}

void IIC_end() {
  digitalWrite(IIC_SCL, LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA, LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SCL, HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA, HIGH);
  delayMicroseconds(3);
}
