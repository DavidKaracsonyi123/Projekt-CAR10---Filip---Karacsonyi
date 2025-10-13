#include <Arduino.h>

int IRSensor = A1; // Sensor am Pin A0

void setup() {
  Serial.begin(9600); // Serielle Verbindung starten
}

void loop() {
  int adcWert = analogRead(IRSensor); // Sensorwert lesen (0-1023)
  
  Serial.print("ADC Wert: ");
  Serial.println(adcWert);
  
  delay(200); // alle 200 ms aktualisieren
}
