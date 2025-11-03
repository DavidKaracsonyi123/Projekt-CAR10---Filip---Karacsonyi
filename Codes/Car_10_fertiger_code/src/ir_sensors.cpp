/**
 * Autonom Driving Car - CAR-10
 * Algorithm to navigate through the race track as fast as possible
 * (C) 2025 David Karacsonyi, Oskar Filip
 *
 *	file	ir_sensors.cpp
 */

#include <Arduino.h>
#include "car10.h"
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
	ir_sensor_front_new = (uint16_t) (15848 / (ir_sensor_front_raw + 11.2)) - 10;

	if(ir_sensor_front_new > 150)
    ir_sensor_front_new = 151;
	else if(ir_sensor_front_new < 20)
    ir_sensor_front_new = 19;


  ir_sensor_right_raw = analogRead(IR_SENSOR_RIGHT);
	ir_sensor_right_new = (uint16_t) (8064 / (ir_sensor_right_raw + 9.4)) - 10;

	if(ir_sensor_right_new > 80)
    ir_sensor_right_new = 81;
	else if(ir_sensor_right_new < 10)
    ir_sensor_right_new = 9;


  ir_sensor_left_raw = analogRead(IR_SENSOR_LEFT);
	ir_sensor_left_new = (uint16_t) (7968 / (ir_sensor_left_raw + 2.8)) - 10;

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
