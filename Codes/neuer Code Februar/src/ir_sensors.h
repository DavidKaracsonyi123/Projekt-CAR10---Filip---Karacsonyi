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

extern uint16_t ir_sensor_front_last;
extern uint16_t ir_sensor_right_last;
extern uint16_t ir_sensor_left_last;

extern int16_t diff_left_right;

#define IR_SENSOR_FRONT           A0
#define IR_SENSOR_RIGHT           A2
#define IR_SENSOR_LEFT            A1

#define AVERAGING 1


#define PARAM_M_FRONT 15848
#define PARAM_D_FRONT 11.2
#define PARAM_K_FRONT 10

#define PARAM_M_RIGHT 8064
#define PARAM_D_RIGHT 9.4
#define PARAM_K_RIGHT 10

#define PARAM_M_LEFT 7968
#define PARAM_D_LEFT 2.8
#define PARAM_K_LEFT 10

void measure_ir_distances();