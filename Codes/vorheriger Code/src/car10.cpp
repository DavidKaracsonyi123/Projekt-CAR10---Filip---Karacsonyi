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

// Zustände der State-Maschine
enum State {
  STATE_FORWARD,  // Fahren
  STATE_STOP,     // Stoppen
  STATE_TURN_LEFT, // Nach links drehen
  STATE_TURN_RIGHT // Nach rechts drehen
};

State current_state = STATE_STOP;  // Initialer Zustand ist STOP

void setup() {
  init_motors();
  init_uart();
}

void loop() {
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

  // State-Maschine: Zustandsübergänge basierend auf Sensorwerten
  switch (current_state) {
    case STATE_FORWARD:
      // Zustand: Geradeaus fahren
      if (ir_sensor_right < 200) {
        // Wenn der rechte Sensor zu nah an der Wand ist
        current_state = STATE_TURN_LEFT;  // Wechsel zu TURN_LEFT
      } else if (ir_sensor_right > 400) {
        // Wenn der rechte Sensor zu weit von der Wand entfernt ist
        current_state = STATE_TURN_RIGHT;  // Wechsel zu TURN_RIGHT
      } else {
        // Fahren, wenn der Abstand ideal ist
        drive_forward();
      }
      break;

    case STATE_STOP:
      // Zustand: Stoppen
      stop_motors();
      // Nach einer kurzen Zeit, wechseln wir zu STATE_FORWARD, um weiterzufahren
      delay(1000);  // Hier wartet das Auto 1 Sekunde
      current_state = STATE_FORWARD;  // Wechsel zu DRIVE_FORWARD
      break;

    case STATE_TURN_LEFT:
      // Zustand: Nach links drehen
      turn_left();
      // Warten, bis der Abstand zur Wand korrigiert ist
      if (ir_sensor_right > 200) {
        current_state = STATE_FORWARD;  // Wechsel zurück zu DRIVE_FORWARD
      }
      break;

    case STATE_TURN_RIGHT:
      // Zustand: Nach rechts drehen
      turn_right();
      // Warten, bis der Abstand zur Wand korrigiert ist
      if (ir_sensor_right < 400) {
        current_state = STATE_FORWARD;  // Wechsel zurück zu DRIVE_FORWARD
      }
      break;
  }
}
