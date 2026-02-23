#include <Arduino.h>
#include "autonom_car.h"
#include "motors.h"

void init_motors()
{
  // pin definitions
  pinMode(MOTOR_RIGHT_SPEED, OUTPUT);
  pinMode(MOTOR_LEFT_SPEED, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);

  // stop all engines
  stop();
}

void stop()
{
  analogWrite(MOTOR_RIGHT_SPEED, STOP_SPEED);
  analogWrite(MOTOR_LEFT_SPEED, STOP_SPEED);
  return;
}
