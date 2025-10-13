#include <Arduino.h>

// Sharp GP2Y0A02YK0F Sensor an A0
const int sensorPin = A0;

// Gleichstrommotor 1
int GSM1 = 10;
int in1 = 9;
int in2 = 8;

// Gleichstrommotor 2
int GSM2 = 5;
int in3 = 7;
int in4 = 6;

// Schwellwert für Stopp (40 cm ≈ ADC-Wert 204)
const int stopThreshold = 204;

// Messintervall (in Millisekunden)
const unsigned long measureInterval = 10; // 10 ms → 100 Messungen/Sekunde
unsigned long lastMeasureTime = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(GSM1, OUTPUT);
  pinMode(GSM2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  unsigned long currentTime = millis();

  // nur alle 10 ms eine Messung durchführen
  if (currentTime - lastMeasureTime >= measureInterval) {
    lastMeasureTime = currentTime;

    int sensorValue = analogRead(sensorPin);
    Serial.print("ADC-Wert: ");
    Serial.println(sensorValue);

    if (sensorValue >= stopThreshold) {
      // 🚫 Hindernis erkannt → Motoren stoppen
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      analogWrite(GSM1, 0);
      analogWrite(GSM2, 0);
      Serial.println("Hindernis erkannt! Auto stoppt.");
    } else {
      // ✅ Kein Hindernis → Vorwärts fahren
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(GSM1, 175);

      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(GSM2, 200);

      Serial.println("Fährt vorwärts...");
    }
  }
}
