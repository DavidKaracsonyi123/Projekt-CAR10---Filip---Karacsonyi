/**
 * Autonom Driving Car - CAR-10
 * Algorithm to navigate through the race track as fast as possible
 * (C) 2025 David Karacsonyi, Oskar Filip
 *
 *	file	ir_sensors.h
 */

#ifndef IR_SENSORS_H
#define IR_SENSORS_H

// Externe Variablen für die Sensorwerte
extern uint16_t ir_sensor_front;
extern uint16_t ir_sensor_right;
extern uint16_t ir_sensor_left;

#define IR_SENSOR_FRONT           A0
#define IR_SENSOR_RIGHT           A1
#define IR_SENSOR_LEFT            A2

void measure_ir_distances();

#endif
