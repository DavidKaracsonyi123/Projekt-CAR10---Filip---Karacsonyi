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

const int startpin = 2;  // Start-Taster an D2
const int stoppin = 3;   // Stopp-Taster an D3
bool fahren = false;  // Auto starten oder stoppen

unsigned long lastMeasureTime = 0;
const unsigned long measureInterval = 100; // alle 100 ms messen

// Motorsteuerungsfunktionen
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
  analogWrite(ML, 0);  // Motor links ausschalten

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(MR, 0);  // Motor rechts ausschalten
}

void moveForward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ML, 175);  // Geschwindigkeit des linken Motors

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(MR, 200);  // Geschwindigkeit des rechten Motors
}

void moveLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(ML, 175);  // Geschwindigkeit des linken Motors

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(MR, 200);  // Geschwindigkeit des rechten Motors
}

void moveRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ML, 175);  // Geschwindigkeit des linken Motors

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(MR, 150);  // Geschwindigkeit des rechten Motors
}

// Start- und Stoppfunktionen
void startCar() {
  fahren = true;  // Auto starten
}

void stopCar() {
  fahren = false;  // Auto stoppen
  stopMotors();    // Motoren ausschalten
}

// Setup-Funktion, die nur einmal ausgeführt wird
void setup() {
  Serial.begin(9600);

  // Setup für Motoren und Sensoren
  motorSetup();
  sensorSetup();

  pinMode(startpin, INPUT_PULLUP);  // Start-Taster mit internem Pullup-Widerstand
  pinMode(stoppin, INPUT_PULLUP);  // Stopp-Taster mit internem Pullup-Widerstand
}

// Loop-Funktion, die ständig wiederholt wird
void loop() {
  // Start-Taster Logik
  if (digitalRead(startpin) == LOW) {  // Wenn Start-Taster gedrückt wird
    startCar();  // Auto starten
  }

  // Stopp-Taster Logik
  if (digitalRead(stoppin) == LOW) {  // Wenn Stopp-Taster gedrückt wird
    stopCar();  // Auto stoppen
  }

  // Wenn das Auto fahren soll
  if (fahren) {
    unsigned long currentTime = millis();
    if (currentTime - lastMeasureTime >= measureInterval) {
      lastMeasureTime = currentTime;

      // Sensorwerte einlesen
      int sensorMitte_new = readMitteSensor();
      int sensorLinks_new = readLinksSensor();
      int sensorRechts_new = readRechtsSensor();

      // Entscheiden, ob das Auto geradeaus, nach links oder nach rechts fährt:
      if (sensorMitte_new > sensorLinks_new && sensorMitte_new > sensorRechts_new) {
        moveForward();  // Auto fährt geradeaus
      }
      else if (sensorLinks_new > sensorMitte_new && sensorLinks_new > sensorRechts_new) {
        moveLeft();  // Auto fährt nach links
      }
      else if (sensorRechts_new > sensorMitte_new && sensorRechts_new > sensorLinks_new) {
        moveRight();  // Auto fährt nach rechts
      }
      else {
        stopMotors();  // Wenn keiner der Sensoren den höchsten Wert hat, stoppe das Auto
      }
    }
  }
  else {
    stopMotors();  // Auto stoppen
  }
}
