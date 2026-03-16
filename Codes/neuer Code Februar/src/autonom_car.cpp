/**
 * Autonom Driving Car - Crazy Car
 * Algorithm to navigate through the race track as fast as possible
 * (C) 2025 Philipp Jahn
 * 
 * Version includes:
 * - Some kind of timeslices
 * - stable sensor values
 * 
 * Todos: 
 * - Todo tags to be checked
 * - speed sensors
 */

#include <Arduino.h>
#include "autonom_car.h"
#include "ir_sensors.h"
#include "motors.h"

// Global variables
bool drive_left_backward = FALSE;   // input for speed sensors
bool drive_right_backward = FALSE;  // input for speed sensors

// Static variables for loop function
static uint8_t state_new = EMERGENCY_STOP;
static uint8_t state = EMERGENCY_STOP;
static uint8_t state_old = EMERGENCY_STOP;
static uint8_t speed_left = 0;
static uint8_t speed_right = 0;
static unsigned long previous_millis_100ms = 0;
static unsigned long previous_millis_20ms = 0;

// ========== Helper Functions ==========

uint8_t add16(uint8_t summand1, int16_t summand2)
{
  int16_t result = (int16_t)summand1 + summand2;
  if (result > 255)
    return 255;
  if (result < 0)
    return 0;
  return (uint8_t)result;
}

uint8_t diff16(uint8_t minuend, int16_t subtrahend)
{
  int16_t result = (int16_t)minuend - subtrahend;
  if (result > 255)
    return 255;
  if (result < 0)
    return 0;
  return (uint8_t)result;
}


// ========== Initialization Functions ==========

void init_debug(void)
{
  pinMode(DEBUG_LED, OUTPUT);
}

void init_buttons(void)
{
  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_BLACK, INPUT_PULLUP);
}

void init_safety(void)
{
  pinMode(BATTERY_CHECK, INPUT);
}

void init_uart(void)
{
  Serial.begin(BAUD);
  Serial.println("Serial started...");
}

void setup(void)
{
  init_debug();
  init_motors();
  init_buttons();
  init_safety();
  init_uart();
}


// ========== Input Handling Functions ==========

void handle_button_inputs(void)
{
  // Emergency stop has highest priority
  if (digitalRead(BUTTON_RED) == LOW)
  {
    state_new = EMERGENCY_STOP;
  }
  else if (digitalRead(BUTTON_BLACK) == LOW)
  {
    state_new = STOP;
  }
}

float read_battery_voltage(void)
{
  uint16_t battery_measurement = analogRead(BATTERY_CHECK);
  // Voltage divided by 690/220 and 1024 = 5V and times 10 to get one decimal digit
  return (float)battery_measurement * 3.1364 * 0.004883 * 10;
}

// ========== Display and Debug Functions ==========

void debug_output(float battery_voltage)
{
  // Debug output to serial
  Serial.print("State: \t");
  Serial.print(state);
  Serial.print("\tBatt: \t");
  Serial.print(battery_voltage);
  Serial.print("\tFront: \t");
  Serial.print(ir_sensor_front);
  Serial.print("\tRight: \t");
  Serial.print(ir_sensor_right);
  Serial.print("\tLeft: \t");
  Serial.print(ir_sensor_left);
  Serial.print("\tDiff: \t");
  Serial.println(diff_left_right);
}

// ========== Strategy Implementation Functions ==========
  

void strategy_middle_control(void)
{
  // TODO implement
}

void strategy_side_control_right(void)
{
  // Check for sharp turns
  if (ir_sensor_front < 95 && diff_left_right < 0)
  {
    state_new = SHARP_RIGHT;
  }
  else if (ir_sensor_front < 95 && diff_left_right > 0)
  {
    state_new = SHARP_LEFT;
  }

  // Speed control based on front distance
  if (ir_sensor_front > FORWARD_MAX_SPEED_THRESHOLD)
  {
    speed_left = MAX_SPEED;
    speed_right = speed_left;
  }
  else if (ir_sensor_front <= FORWARD_MAX_SPEED_THRESHOLD && ir_sensor_front > BACKWARD_THRESHOLD)
  {
    speed_left = ir_sensor_front * SPEED_CONTROL_K + SPEED_CONTROL_D;
    speed_right = speed_left;
  }
  else
  {
    speed_left = STOP_SPEED;
    speed_right = STOP_SPEED;
    state_new = DRIVE_BACKWARD;
  }

  // Steering based on right sensor
  if (ir_sensor_right > SIDE_DISTANCE)
  {
    speed_right = speed_right * SIDECONTROL_FACTOR;
    if (ir_sensor_front < 90 || ir_sensor_right >= 80)
      speed_right = 0;
  }
  else if (ir_sensor_right < SIDE_DISTANCE)
  {
    speed_left = speed_left * SIDECONTROL_FACTOR;
    if (ir_sensor_front < 90 || ir_sensor_left >= 80)
      speed_left = 0;
  }
}

void strategy_side_control_left_basic(void)
{
  speed_left = MID_SPEED;
  speed_right = speed_left;

  if (ir_sensor_left < 40)
  {
    speed_right = speed_right * 0.3;
  }
  else if (ir_sensor_left > 40)
  {
    speed_left = speed_left * 0.3;
  }

  if (ir_sensor_front < BACKWARD_THRESHOLD)
  {
    speed_left = STOP_SPEED;
    speed_right = STOP_SPEED;
    state_new = DRIVE_BACKWARD;
  }
}

void strategy_side_control_left_improved(void)
{
  speed_left = MAX_SPEED - 30;
  speed_right = speed_left;

  if (ir_sensor_left < 40)
  {
    speed_right = speed_right * 0.5;
    if (ir_sensor_front < 90 || ir_sensor_right >= 80)
      speed_right = speed_right * 0.1;
  }
  else if (ir_sensor_left > 40)
  {
    speed_left = speed_left * 0.5;
    if (ir_sensor_front < 90 || ir_sensor_left >= 80)
      speed_left = speed_left * 0.1;
  }

  if (ir_sensor_front < BACKWARD_THRESHOLD)
  {
    speed_left = STOP_SPEED;
    speed_right = STOP_SPEED;
    state_new = DRIVE_BACKWARD;
  }
}

void strategy_pid_control(void)
{
  static const float Kp = 1.0;  // Proportional
  static const float Ki = 0.0; // Integral
  static const float Kd = 0.0;  // Derivativ

  static int16_t last_error = 0;
  static float integral = 0;

  int16_t error = diff_left_right; 
  integral += error;
  if (integral > 100) integral = 100;
  if (integral < -100) integral = -100;
  int16_t derivative = error - last_error;
  last_error = error;
  float control_output = (Kp * error) + (Ki * integral) + (Kd * derivative);
  uint8_t base_speed = MID_SPEED;
  if (ir_sensor_front < 100) base_speed = MIN_SPEED + 20;
  speed_left = add16(base_speed, -control_output);
  speed_right = add16(base_speed, control_output);

  if (ir_sensor_front < BACKWARD_THRESHOLD)
  {
    speed_left = STOP_SPEED;
    speed_right = STOP_SPEED;
    state_new = DRIVE_BACKWARD;
    integral = 0;
  }
}

// ========== State Machine Functions ==========

void handle_emergency_stop(void)
{
  speed_left = STOP_SPEED;
  speed_right = STOP_SPEED;
}

void handle_stop(void)
{
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
}

void handle_drive_forward(void)
{
  // Transition handling
  if (state_old == DRIVE_BACKWARD)
  {
    digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
    digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
    analogWrite(MOTOR_RIGHT_SPEED, STOP_SPEED);
    analogWrite(MOTOR_LEFT_SPEED, STOP_SPEED);
    delay(300);  // avoid too fast switching from backward to forward
  }

  drive_left_backward = FALSE;
  drive_right_backward = FALSE;

  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);

  // Execute selected strategy
  #if STRATEGY == 0
    strategy_middle_control();
  #elif STRATEGY == 1
    strategy_side_control_right();
  #elif STRATEGY == 2
    strategy_side_control_left_basic();
  #elif STRATEGY == 3
    strategy_side_control_left_improved();
  #elif STRATEGY == 4
    strategy_pid_control();
  #endif
}

void handle_drive_backward(void)
{
  // Transition handling
  if (state_old != DRIVE_BACKWARD)
  {
    digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
    digitalWrite(MOTOR_LEFT_FORWARD, LOW);
    analogWrite(MOTOR_RIGHT_SPEED, STOP_SPEED);
    analogWrite(MOTOR_LEFT_SPEED, STOP_SPEED);
    delay(300);  // avoid fast switching from forward to backward
  }

  drive_left_backward = TRUE;
  drive_right_backward = TRUE;

  digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);

  speed_left = MID_SPEED;
  speed_right = speed_left;

  if (ir_sensor_front >= FORWARD_THRESHOLD)
  {
    speed_left = STOP_SPEED;
    speed_right = STOP_SPEED;
    state_new = DRIVE_FORWARD;
  }
}

void handle_sharp_left(void)
{
  speed_left = MIN_SPEED;
  speed_right = MAX_SPEED;

  if (ir_sensor_front > 120)
  {
    state_new = DRIVE_FORWARD;
  }
  else if (ir_sensor_front < BACKWARD_THRESHOLD)
  {
    speed_left = STOP_SPEED;
    speed_right = STOP_SPEED;
    state_new = DRIVE_BACKWARD;
  }
}

void handle_sharp_right(void)
{
  speed_left = MAX_SPEED;
  speed_right = MIN_SPEED;

  if (ir_sensor_front > 120)
  {
    state_new = DRIVE_FORWARD;
  }
  else if (ir_sensor_front < BACKWARD_THRESHOLD)
  {
    speed_left = STOP_SPEED;
    speed_right = STOP_SPEED;
    state_new = DRIVE_BACKWARD;
  }
}

void process_state_machine(void)
{
  state_old = state;
  state = state_new;

  switch (state)
  {
    case EMERGENCY_STOP:
      handle_emergency_stop();
      break;

    case STOP:
      handle_stop();
      break;

    case DRIVE_FORWARD:
      handle_drive_forward();
      break;

    case DRIVE_BACKWARD:
      handle_drive_backward();
      break;

    case SHARP_LEFT:
      handle_sharp_left();
      break;

    case SHARP_RIGHT:
      handle_sharp_right();
      break;

    default:
      break;
  }
}

void apply_motor_speeds(void)
{
  analogWrite(MOTOR_RIGHT_SPEED, speed_right);
  analogWrite(MOTOR_LEFT_SPEED, speed_left);
}

// ========== Main Loop ==========

void loop(void)
{
  float battery_voltage;

  // Handle button inputs (highest priority)
  handle_button_inputs();

  // Read battery voltage
  battery_voltage = read_battery_voltage();

  // 100ms timeslice: Display and debug output
  if (millis() - previous_millis_100ms >= 100)
  {
    previous_millis_100ms = millis();
    debug_output(battery_voltage);
  }

  // 20ms timeslice: Control loop
  if (millis() - previous_millis_20ms >= 20)
  {
    previous_millis_20ms = millis();

    // Update sensor readings
    measure_ir_distances();

    // Process state machine
    process_state_machine();

    // Apply motor speeds
    apply_motor_speeds();
  }
}
