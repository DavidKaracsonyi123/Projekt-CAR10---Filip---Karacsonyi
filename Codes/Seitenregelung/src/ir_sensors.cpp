#include "ir_sensors.h"
#include <Arduino.h>

// Pinbelegung der IR-Sensoren
const int IR_SENSOR_MITTE = A0;   // GP2Y0A02YK0F
const int IR_SENSOR_LINKS = A1;   // GP2Y0A21YK0F
const int IR_SENSOR_RECHTS = A2;  // GP2Y0A21YK0F

void sensorSetup() {
  pinMode(IR_SENSOR_MITTE, INPUT);
  pinMode(IR_SENSOR_LINKS, INPUT);
  pinMode(IR_SENSOR_RECHTS, INPUT);
}

int readMitteSensor() {
  int sensorMitte_raw = analogRead(IR_SENSOR_MITTE);
  int sensorMitte_new = (int)(15848 / (sensorMitte_raw + 11.2) - 10);
  if (sensorMitte_new > 150) sensorMitte_new = 151;
  else if (sensorMitte_new < 20) sensorMitte_new = 19;
  return sensorMitte_new;
}

int readLinksSensor() {
  int sensorLinks_raw = analogRead(IR_SENSOR_LINKS);
  int sensorLinks_new = (int)(7968 / (sensorLinks_raw + 2.8) - 10);
  if (sensorLinks_new > 80) sensorLinks_new = 81;
  else if (sensorLinks_new < 10) sensorLinks_new = 9;
  return sensorLinks_new;
}

int readRechtsSensor() {
  int sensorRechts_raw = analogRead(IR_SENSOR_RECHTS);
  int sensorRechts_new = (int)(8064 / (sensorRechts_raw + 9.4) - 10);
  if (sensorRechts_new > 80) sensorRechts_new = 81;
  else if (sensorRechts_new < 10) sensorRechts_new = 9;
  return sensorRechts_new;
}
