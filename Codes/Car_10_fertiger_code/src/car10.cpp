/**
 * Autonom Driving Car - CAR-10
 * Algorithm to navigate through the race track as fast as possible
 * (C) 2025 David Karacsonyi, Oskar Filip
 *
 *	file	car10.cpp
 */

#include <Arduino.h>
#include "car10.h"
#include "ir_sensors.h"

// Motorsteuerung
void init_motors() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);  // PWM für linken Motor
  pinMode(ENB, OUTPUT);  // PWM für rechten Motor
}

void drive_forward() {
  // Linker Motor vorwärts
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 175);     // Geschwindigkeit des linken Motors

  // Rechter Motor vorwärts
  digitalWrite(IN3, LOW);  // Rechter Motor vorwärts
  digitalWrite(IN4, HIGH); // Rechter Motor vorwärts
  analogWrite(ENB, 175);     // Geschwindigkeit des rechten Motors
}

void stop_motors() {
  // Stoppen der Motoren
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);  // Motor anhalten
  analogWrite(ENB, 0);  // Motor anhalten
}

void turn_left() {
  // Langsame Drehung nach links
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 150); // Langsame Drehung links
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 200); // Schnellere Drehung rechts
}

void turn_right() {
  // Langsame Drehung nach rechts
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 200); // Schnellere Drehung links
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 150); // Langsame Drehung rechts
}

void init_uart() {
  Serial.begin(115200);  // Serielle Kommunikation mit der definierten Baudrate
  Serial.println("Serial started...");
}

void setup() {
  init_motors();
  init_uart();
}

void loop() {
  static uint8_t state_new = DRIVE_FORWARD;
  static uint8_t state = DRIVE_FORWARD;

  static unsigned long previous_millis_100ms = 0;

  // Zeitscheiben - alle 100ms ausführen
  if (millis() - previous_millis_100ms >= 100) {
    previous_millis_100ms = millis();

    // Sensorwerte auf dem Monitor ausgeben
    Serial.print("Front: \t"); Serial.print(ir_sensor_front); 
    Serial.print("\tRight: \t"); Serial.print(ir_sensor_right); 
    Serial.print("\tLeft: \t"); Serial.println(ir_sensor_left);
  }

  // Sensorwerte alle 20ms lesen
  measure_ir_distances();

  // Entscheidungslogik für das Ausweichen und Fahren
  if (ir_sensor_front > 300 && ir_sensor_front < 400) {  // Wenn 40cm erkannt werden
    // Die Erkennung für 40cm (mit ADC-Werten von ca. 300-400)
    turn_right();  // Nach rechts abbiegen
  } else {
    drive_forward();  // Wenn kein Hindernis erkannt, geradeaus fahren
  }
}
