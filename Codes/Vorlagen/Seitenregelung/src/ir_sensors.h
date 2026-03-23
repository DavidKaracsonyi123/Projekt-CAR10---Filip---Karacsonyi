#ifndef IR_SENSORS_H
#define IR_SENSORS_H

// IR Sensor Pins
extern const int IR_SENSOR_MITTE;
extern const int IR_SENSOR_LINKS;
extern const int IR_SENSOR_RECHTS;

void sensorSetup();
int readMitteSensor();
int readLinksSensor();
int readRechtsSensor();

#endif
