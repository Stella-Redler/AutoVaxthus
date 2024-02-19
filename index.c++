#include <Servo.h>
#define AOUT_PIN A0
#define PUMP_PIN 5

Servo myservo;

int temppin = A1;
int threshold = 22;
float tempC;
float value;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(PUMP_PIN, OUTPUT);
}

void loop() {
  readTemp();
  readMoist();
  updateServo();
  pump();
}

void readTemp() {
  int reading = analogRead(temppin);   // getting the voltage reading from the temperature sensor
  float voltage = (float)reading * 5.0;  // convert the analog reading (0 to 1023) to voltage (0 - 5V)
  voltage /= 1024.0;
  tempC = (voltage - 0.5) * 10;     // convert voltage to degree Celsius including the 500mV offset adjustment
  Serial.print(tempC);
  Serial.println(" degrees C");
}

void readMoist() {
  value = analogRead(AOUT_PIN);
  Serial.print("Moisture: ");
  Serial.println(value);
  return value;
  delay(5000);
}


void updateServo() {
  if (tempC > threshold) {
    myservo.write(45);
  } else {
    myservo.write(0);
  }
}

void pump() {
  if (value > 700) {
    digitalWrite(PUMP_PIN, HIGH);
  } else {
    digitalWrite(PUMP_PIN, LOW);
  }
}