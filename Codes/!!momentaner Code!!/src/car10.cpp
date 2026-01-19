#include "car10.h"
#include "ir_sensors.h"
#include <Arduino.h>

// Motor Pins
int ML = 10;
int in1 = 9;
int in2 = 8;
int MR = 5;
int in3 = 7;
int in4 = 6;

const int startpin = 2;
const int stoppin = 3;
bool fahren = false;

unsigned long lastMeasureTime = 0;
const unsigned long measureInterval = 45;

// Definition der Fahrzustände für das switch-case
enum Fahrzustand {
  STOPP,
  VORWAERTS,
  LINKS,
  RECHTS,
  LANGSAM
};

void motorSetup() {
  pinMode(ML, OUTPUT);
  pinMode(MR, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(ML, 0);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(MR, 0);
}

void moveForward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ML, 255);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(MR, 255);
}

void moveLeft() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ML, 50);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(MR, 150);
}

void moveRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ML, 150);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(MR, 50);
}

void moveslow() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ML, 80);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(MR, 80);
}

void startCar() { fahren = true; }
void stopCar() {
  fahren = false;
  stopMotors();
}

void setup() {
  Serial.begin(9600);
  motorSetup();
  sensorSetup();
  pinMode(startpin, INPUT_PULLUP);
  pinMode(stoppin, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(startpin) == LOW) startCar();
  if (digitalRead(stoppin) == LOW) stopCar();

  if (fahren) {
    unsigned long currentTime = millis();
    if (currentTime - lastMeasureTime >= measureInterval) {
      lastMeasureTime = currentTime;

      int sensorMitte = readMitteSensor();
      int sensorLinks = readLinksSensor();
      int sensorRechts = readRechtsSensor();

      // Hilfsvariable zur Bestimmung des Modus
      Fahrzustand aktuellerModus = STOPP;

      // Logik zur Bestimmung des Modus (Priorisierung)
      if (sensorMitte > sensorLinks && sensorMitte > sensorRechts) {
        aktuellerModus = VORWAERTS;
      } 
      else if (sensorLinks > sensorMitte && sensorLinks > sensorRechts) {
        aktuellerModus = LINKS;
      } 
      else if (sensorRechts > sensorMitte && sensorRechts > sensorLinks) {
        aktuellerModus = RECHTS;
      } 
      else if (sensorRechts == sensorLinks) {
        aktuellerModus = LINKS;
      } 
      else if (sensorMitte < 50) {
        aktuellerModus = LANGSAM;
      }

      // Die eigentliche Motorsteuerung per switch-case
      switch (aktuellerModus) {
        case VORWAERTS:
          moveForward();
          break;
        case LINKS:
          moveLeft();
          break;
        case RECHTS:
          moveRight();
          break;
        case LANGSAM:
          moveslow();
          break;
        case STOPP:
        default:
          stopMotors();
          break;
      }
    }
  } else {
    stopMotors();
  }
}