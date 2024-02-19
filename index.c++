/*
Namn: Stella Redler
Fil: Automatiskt växthus
Datum: 2024-02-19
Beskrivning: Detta program gör så det vattnas och regleras temperatur automatiskt i ett växthus. Den skriver även ut alla värden i seriell monitor, så det blir lättare att hålla koll på växtens behov och tillstånd.
*/

/*Inkluderar alla bibliotek och definierar alla pins*/
#include <Servo.h>
#define AOUT_PIN A0
#define PUMP_PIN 5

Servo myservo;

/*Initierar alla globala variabler*/
int temppin = A1;
int threshold = 22;
float tempC;
float value;

void setup() {
  Serial.begin(9600);   // Startar seriell monitor
  myservo.attach(9);
  pinMode(PUMP_PIN, OUTPUT);
}

/*Loopar alla nedanstående delar av programmet i den ordning de står*/
void loop() {
  readTemp();
  readMoist();
  updateServo();
  pump();
}

void readTemp() {
  int reading = analogRead(temppin);    // hämtar output värdet från termometern
  float voltage = (float)reading * 5.0; // konverterar det analoga inputet (0 to 1023) till volt (0 - 5V)
  voltage /= 1024.0;
  tempC = (voltage - 0.5) * 10;         // konverterar volt till grader i celcius inklusive 500mV offsettjustering
  Serial.print(tempC);                  // Skriver ut output i seriell monitor
  Serial.println(" degrees C");         // skriver ut " degrees C" i seriell monitor
}

void readMoist() {
  value = analogRead(AOUT_PIN);
  Serial.print("Moisture: ");   // skriver ut "Moisture: " i seriell monitor
  Serial.println(value);        // skriver ut värdet i seriell monitor
  return value;
  delay(5000);                  // väntar 5 sekunder
}


void updateServo() {
  if (tempC > threshold) {
    myservo.write(45);      // ändrar servons position till 45 grader
  } else {
    myservo.write(0);       // ändrar servons position till 0 grader
  }
}

void pump() {
  if (value > 700) {
    digitalWrite(PUMP_PIN, HIGH);   // ger input HIGH (ström på) till PUMP_PIN
  } else {
    digitalWrite(PUMP_PIN, LOW);    // ger input LOW (ström av) till PUMP_PIN
  }
}