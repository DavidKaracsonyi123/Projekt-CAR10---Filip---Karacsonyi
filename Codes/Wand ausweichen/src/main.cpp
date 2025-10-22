#include <Arduino.h>

// Pinbelegung der Sharp-Sensoren
#define IR_SENSOR_MITTE  A0   // Sensor Mitte
#define IR_SENSOR_LINKS  A1   // Sensor links
#define IR_SENSOR_RECHTS A2   // Sensor rechts

// Pinbelegung der Motoren
int GSM1 = 10;  // Motor links
int in1 = 9;
int in2 = 8;
int GSM2 = 5;   // Motor rechts
int in3 = 7;
int in4 = 6;

// Messintervall
const unsigned long measureInterval = 100; // alle 100 ms messen
unsigned long lastMeasureTime = 0;

void setup() {
  // PinMode für die Motoren setzen
  pinMode(GSM1, OUTPUT);
  pinMode(GSM2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastMeasureTime >= measureInterval) {
    lastMeasureTime = currentTime;

    // Messungen der Sensoren
    uint16_t sensorMitte_raw  = analogRead(IR_SENSOR_MITTE);
    uint16_t sensorLinks_raw  = analogRead(IR_SENSOR_LINKS);
    uint16_t sensorRechts_raw = analogRead(IR_SENSOR_RECHTS);

    uint16_t sensorMitte_new = (uint16_t)(15848 / (sensorMitte_raw + 11.2) - 10);
    if (sensorMitte_new > 150) {
      sensorMitte_new = 151;
    } else if (sensorMitte_new < 20) {
      sensorMitte_new = 19;
    }

    uint16_t sensorLinks_new = (uint16_t)(7968 / (sensorLinks_raw + 2.8) - 10);
    if (sensorLinks_new > 80) {
      sensorLinks_new = 81;
    } else if (sensorLinks_new < 10) {
      sensorLinks_new = 9;
    }

    uint16_t sensorRechts_new = (uint16_t)(8064 / (sensorRechts_raw + 9.4) - 10);
    if (sensorRechts_new > 80) {
      sensorRechts_new = 81;
    } else if (sensorRechts_new < 10) {
      sensorRechts_new = 9;
    }

    digitalWrite(in1, LOW); 
    digitalWrite(in2, HIGH);
    analogWrite(GSM1, 175); 
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(GSM2, 200); 
    delay(2000);
    digitalWrite(in1, HIGH); 
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, HIGH);

    // Wenn der Abstand rechts größer als 50 cm ist, dreht das Auto nach links
    if (sensorRechts_new > 50) {
      // Drehe nach links (Auto ausweichen) für nur kurze Zeit
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(GSM1, 175); // Geschwindigkeit Motor 1
      digitalWrite(in3, LOW); // Stoppe Motor 2
      digitalWrite(in4, LOW);
      analogWrite(GSM2, 0);
      delay(300); // Kurze Zeit (300 ms) nach links lenken

      // Setze die Motoren wieder auf Vorwärtsfahrt
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(GSM1, 175           ); // Geschwindigkeit Motor 1
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(GSM2, 200); // Geschwindigkeit Motor 2
    }

     if (sensorLinks_new > 50) {
      // Drehe nach links (Auto ausweichen) für nur kurze Zeit
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(GSM1, 0); // Geschwindigkeit Motor 1
      digitalWrite(in3, HIGH); // Stoppe Motor 2
      digitalWrite(in4, HIGH);
      analogWrite(GSM2, 200);
      delay(300); // Kurze Zeit (300 ms) nach links lenken

      // Setze die Motoren wieder auf Vorwärtsfahrt
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(GSM1, 175           ); // Geschwindigkeit Motor 1
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(GSM2, 200); // Geschwindigkeit Motor 2
    }

   
    
  }
}
