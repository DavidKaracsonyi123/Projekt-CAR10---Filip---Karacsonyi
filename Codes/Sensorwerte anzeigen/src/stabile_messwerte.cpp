#include <Arduino.h>

//Pinbelegung
#define IR_SENSOR_MITTE  A0   // GP2Y0A02YK0F
#define IR_SENSOR_LINKS  A1   // GP2Y0A21YK0F
#define IR_SENSOR_RECHTS A2   // GP2Y0A21YK0F

//Messintervall
const unsigned long measureInterval = 100; // alle 100 ms messen
unsigned long lastMeasureTime = 0;

void setup() {
  Serial.begin(9600);
  delay(300);
  Serial.println("Starte Messung der 3 Sharp-Sensoren (mit deinen Formeln)...");
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastMeasureTime >= measureInterval) {
    lastMeasureTime = currentTime;

    
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

    //Ausgabe am Serial Monitor
    Serial.print("Links: ");
    Serial.print(sensorLinks_new);
    Serial.print(" cm\tMitte: ");
    Serial.print(sensorMitte_new);
    Serial.print(" cm\tRechts: ");
    Serial.print(sensorRechts_new);
    Serial.println(" cm");
  }
}
