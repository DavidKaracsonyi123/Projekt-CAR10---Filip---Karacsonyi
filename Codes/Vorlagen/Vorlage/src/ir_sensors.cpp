/**
 * Autonom Driving Car - Crazy Car
 * Algorithm to navigate through the race track as fast as possible
 * (C) 2025 Philipp Jahn
 *
 *	file	ir_sensors.cpp
 */

#include <Arduino.h>
#include "autonom_car.h"
#include "ir_sensors.h"

uint16_t ir_sensor_front = 70;
uint16_t ir_sensor_right = 30;
uint16_t ir_sensor_left = 30;

int16_t diff_left_right;


void measure_ir_distances()
{
  uint16_t ir_sensor_front_raw, ir_sensor_right_raw, ir_sensor_left_raw;
  uint16_t ir_sensor_front_new, ir_sensor_right_new, ir_sensor_left_new;

  // read IR sensor data
  ir_sensor_front_raw = analogRead(IR_SENSOR_FRONT);
	ir_sensor_front_new = (uint16_t) (15561.8 / (ir_sensor_front_raw + 25.59)) - 7;

	if(ir_sensor_front_new > 150)
    ir_sensor_front_new = 151;
	else if(ir_sensor_front_new < 20)
    ir_sensor_front_new = 19;


  ir_sensor_right_raw = analogRead(IR_SENSOR_RIGHT);
	ir_sensor_right_new = (uint16_t) (5829.12 / (ir_sensor_right_raw - 2.902)) - 2;

	if(ir_sensor_right_new > 80)
    ir_sensor_right_new = 81;
	else if(ir_sensor_right_new < 10)
    ir_sensor_right_new = 9;


  ir_sensor_left_raw = analogRead(IR_SENSOR_LEFT);
	ir_sensor_left_new = (uint16_t) (6346.62 / (ir_sensor_left_raw - 2.252)) - 3;

	if(ir_sensor_left_new > 80)
    ir_sensor_left_new = 81;
	else if(ir_sensor_left_new < 10)
    ir_sensor_left_new = 9;

  #if AVERAGING == 1
    ir_sensor_front = (ir_sensor_front + ir_sensor_front_new) / 2;
    ir_sensor_right = (ir_sensor_right + ir_sensor_right_new) / 2;
    ir_sensor_left = (ir_sensor_left + ir_sensor_left_new) / 2;
  #else
    ir_sensor_front = ir_sensor_front_new;
    ir_sensor_right = ir_sensor_right_new;
    ir_sensor_left = ir_sensor_left_new;
  #endif

  // calculate difference of right and left
  diff_left_right = ir_sensor_left - ir_sensor_right;

}
