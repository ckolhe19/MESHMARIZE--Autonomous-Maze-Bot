// MESHMERIZE - Autonomous Maze Solving Bot
// Techfest IIT Bombay 2026 | PCE Nagpur Zonals
// Author: Chetan Kolhe
// Hardware: Arduino UNO + 5x IR Sensors + L298N

// IR Sensors (A0 to A4)
#define IR1 A0
#define IR2 A1
#define IR3 A2
#define IR4 A3
#define IR5 A4

// L298N Motor Driver Pins
#define ENA 9
#define ENB 10
#define IN1 8
#define IN2 7
#define IN3 6
#define IN4 5

int baseSpeed = 150;

void setup() {
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);
  
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  int s1 = analogRead(IR1);
  int s2 = analogRead(IR2);
  int s3 = analogRead(IR3);
  int s4 = analogRead(IR4);
  int s5 = analogRead(IR5);

  // Black Line Logic (20-30 = Black, 1000+ = White)
  bool left2 = s1 < 100;
  bool left1 = s2 < 100;
  bool center = s3 < 100;
  bool right1 = s4 < 100;
  bool right2 = s5 < 100;

  // Straight
  if (center) {
    forward();
  }
  // Slight left/right correction
  else if (left1) {
    slightLeft();
  }
  else if (right1) {
    slightRight();
  }
  // Sharp turns at junction
  else if (left2) {
    sharpLeft();
  }
  else if (right2) {
    sharpRight();
  }
  else {
    stopBot();
  }
}

void forward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, baseSpeed); analogWrite(ENB, baseSpeed);
}
void slightLeft() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, 80); analogWrite(ENB, 180);
}
void slightRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, 180); analogWrite(ENB, 80);
}
void sharpLeft() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, 180); analogWrite(ENB, 180);
}
void sharpRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, 180); analogWrite(ENB, 180);
}
void stopBot() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}