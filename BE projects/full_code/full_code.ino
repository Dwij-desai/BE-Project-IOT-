#include <Servo.h>

#define S0 2
#define S1 3
#define S2 4
#define S3 7
#define sensorOut 8

Servo myServo1;
Servo myServo2;
int pos = 0;

// Stores frequency read by the photodiodes
int red = 0;
int green = 0;
int blue = 0;
int benar = 0;
int warna = 0;

// Define color detection threshold values
const int redThreshold = 150;
const int greenThreshold = 90;
const int blueThreshold = 60;

void setup() {
  myServo1.attach(5);
  myServo2.attach(6);

  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);

  // Setting frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Begins serial communication
  Serial.begin(9600);
}

void loop() {
  myServo2.write(0); // Move servo2 to position 0
  delay(1000);
  benar = 0;

  while (benar == 0) {
    detectColor();
    posServo();
    delay(100);
  }

  delay(200);
  myServo2.write(70); // Move servo2 to position 70
  benar = 0;
  delay(1000);
}

void detectColor() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  // Reading the output frequency
  red = pulseIn(sensorOut, LOW);

  // Printing the RED (R) value
  Serial.print("R = ");
  Serial.print(red);
  delay(100);

  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  green = pulseIn(sensorOut, LOW);

  // Printing the GREEN (G) value
  Serial.print(" G = ");
  Serial.print(green);
  delay(100);

  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  blue = pulseIn(sensorOut, LOW);

  // Printing the BLUE (B) value
  Serial.print(" B = ");
  Serial.println(blue);
  delay(100);

  if (blue < blueThreshold && red < redThreshold && green < greenThreshold) {
    warna = 1;
    Serial.println("biru");
  } else if ((50 < red && red < 83) && (110 < green && green < 150) && blue < 100) {
    warna = 2;
    Serial.println("Merah");
  } else if ((120 < red && red < 150) && (70 < green && green < 90) && (60 < blue && blue < 85)) {
    warna = 3;
    Serial.println("Hijau");
  } else if ((43 < red && red < 70) && (55 < green && green < 80) && (60 < blue && blue < 80)) {
    warna = 4;
    Serial.println("Kuning");
  } else if ((90 < red && red < 105) && (90 < green && green < 115) && blue < 55) {
    warna = 5;
    Serial.println("Ungu");
  } else {
    warna = 0;
    Serial.println("tidak mendeteksi");
  }
}

void posServo() {
  if (warna == 1) {
    myServo1.write(30);
    benar = 1;
  } else if (warna == 2) {
    myServo1.write(60);
    benar = 1;
  } else if (warna == 3) {
    myServo1.write(90);
    benar = 1;
  } else if (warna == 4) {
    myServo1.write(120);
    benar = 1;
  } else if (warna == 5) {
    myServo1.write(150);
    benar = 1;
  }
}
