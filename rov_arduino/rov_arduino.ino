#define IIC_SCL A5
#define IIC_SDA A4

unsigned char current_state = 0;  // 0: stopped, 1: forward, 2: left, 3: right

void IIC_start();
void IIC_send(unsigned char send_data);
void IIC_end();

// Define 4 different images for each state
unsigned char images[4][16] = {
  { 0x00,0x08,0x08,0x00,0x00,0x30,0x30,0x08,0x08,0x30,0x30,0x00,0x00,0x08,0x08,0x00 },  // Stopped
  { 0x00,0x0C,0x0C,0x00,0x00,0x30,0x30,0x08,0x08,0x30,0x30,0x00,0x00,0x0C,0x0C,0x00 },  // Forward
  { 0x00,0x08,0x0C,0x00,0x00,0x30,0x30,0x08,0x08,0x30,0x30,0x00,0x00,0x08,0x0C,0x00 },  // Left
  { 0x00,0x0C,0x08,0x00,0x00,0x30,0x30,0x08,0x08,0x30,0x30,0x00,0x00,0x0C,0x08,0x00 }   // Right
};

void setup() {
  pinMode(IIC_SCL, OUTPUT);
  pinMode(IIC_SDA, OUTPUT);
  digitalWrite(IIC_SCL, LOW);
  digitalWrite(IIC_SDA, LOW);

  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(0, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  Serial.begin(9600);
}
void loop() {
  int lowSpeed = 10;   // Low speed value
  int highSpeed = 250;  // High speed value

  int leftState = digitalRead(0);
  int forwardState = digitalRead(9);
  int rightState = digitalRead(1);

  Serial.print("Left: ");
  Serial.print(leftState);
  Serial.print(" Forward: ");
  Serial.print(forwardState);
  Serial.print(" Right: ");
  Serial.println(rightState);

  // Determine current state and control motors
  if (forwardState == HIGH && rightState == HIGH) {
    Serial.println("STOPPED");
    current_state = 0;  // Stopped
    stopMotors();
  } else if (forwardState == LOW) {
    Serial.println("FORWARD");
    current_state = 1;  // Forward
    moveForward(highSpeed);
  } else if (leftState == LOW) {
    Serial.println("LEFT");
    current_state = 2;  // Left
    turnLeft(highSpeed, lowSpeed);
  } else if (rightState == LOW) {
    Serial.println("RIGHT");
    current_state = 3;  // Right
    turnRight(highSpeed, lowSpeed);
  }

  updateDisplay();
  delay(100);
}

void moveForward(int speed) {
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  analogWrite(6, speed);
  analogWrite(5, speed);
}

void turnLeft(int highSpeed, int lowSpeed) {
  digitalWrite(2, LOW);
  analogWrite(6, lowSpeed);
  digitalWrite(4, HIGH);
  analogWrite(5, highSpeed);
}

void turnRight(int highSpeed, int lowSpeed) {
  digitalWrite(2, HIGH);
  analogWrite(6, highSpeed);
  digitalWrite(4, LOW);
  analogWrite(5, lowSpeed);
}

void stopMotors() {
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  analogWrite(6, 0);
  analogWrite(5, 0);
}

void updateDisplay() {
  // Display control
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
  IIC_send(0x8A);  // Set brightness
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