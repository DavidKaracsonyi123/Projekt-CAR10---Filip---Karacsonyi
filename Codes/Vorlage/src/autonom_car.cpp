/**
 * Autonom Driving Car - Crazy Car
 * Algorithm to navigate through the race track as fast as possible
 * (C) 2025 Philipp Jahn
 *
 *	file	autonom_car.cpp
 */

#include <Arduino.h>
#include "autonom_car.h"
#include "ir_sensors.h"

void init_buttons()
{
  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_BLACK, INPUT_PULLUP);
}

void init_uart()
{
  // initialize UART Interface
  Serial.begin(BAUD);
  Serial.println("Serial started...");
}

void setup()
{
  init_motors();
  init_buttons();
  init_uart();
}


void loop()
{
  static uint8_t state_new = EMERGENCY_STOP;
  static uint8_t state = EMERGENCY_STOP;
  static uint8_t state_old = EMERGENCY_STOP;

  static uint8_t speed_left = 0, speed_right = 0;

  static unsigned long previous_millis_100ms = 0;

  static unsigned long previous_millis_20ms = 0;

  // highest priority
  if (digitalRead(BUTTON_BLACK) == LOW)
  {
    state_new = STOP;
  }

  if (digitalRead(BUTTON_RED) == LOW)
  {
    state_new = EMERGENCY_STOP;
  }

  // timeslices - to be done every 100ms
  if (millis() - previous_millis_100ms >= 100)
  {
    previous_millis_100ms = millis();

    Serial.print("State: \t"); Serial.print(state); Serial.print("\tFront: \t"); Serial.print(ir_sensor_front); Serial.print("\tRight: \t"); Serial.print(ir_sensor_right); Serial.print("\tLeft: \t"); Serial.print(ir_sensor_left);
  }

  // timeslices - to be done every 20ms
  if (millis() - previous_millis_20ms >= 20)
  {
    previous_millis_20ms = millis();

    measure_ir_distances();

    state_old = state;
    state = state_new;

    switch (state)
    {
      case EMERGENCY_STOP:
        speed_left = STOP_SPEED;
        speed_right = STOP_SPEED;

        // only way to start by pressing the start button
        break;

      case STOP:
        speed_left = STOP_SPEED;
        speed_right = STOP_SPEED;

        if (ir_sensor_front >= FORWARD_THRESHOLD)
        {
          state_new = DRIVE_FORWARD;
        }
        else
        {
          state_new = DRIVE_BACKWARD;
        }
        break;

      case DRIVE_FORWARD:
        
        break;

      case DRIVE_BACKWARD:

        break;

      default:
        break;
    }
    
    analogWrite(MOTOR_RIGHT_SPEED, speed_right);
    analogWrite(MOTOR_LEFT_SPEED, speed_left);
  }
  
  return;
}