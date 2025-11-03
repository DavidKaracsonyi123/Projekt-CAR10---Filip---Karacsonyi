/**
 * Autonom Driving Car - Crazy Car
 * Algorithm to navigate through the race track as fast as possible
 * (C) 2025 Philipp Jahn
 *
 *	file	ir_sensors.h
 */

extern uint16_t ir_sensor_front;
extern uint16_t ir_sensor_right;
extern uint16_t ir_sensor_left;

extern int16_t diff_left_right;

#define IR_SENSOR_FRONT           A0
#define IR_SENSOR_RIGHT           A1
#define IR_SENSOR_LEFT            A2

#define AVERAGING 1

void measure_ir_distances();