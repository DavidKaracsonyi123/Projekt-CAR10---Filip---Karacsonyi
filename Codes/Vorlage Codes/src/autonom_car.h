/**
 * Autonom Driving Car - Crazy Car
 * Algorithm to navigate through the race track as fast as possible
 * (C) 2025 Philipp Jahn
 *
 *	file	autonom_car.h
 */
 
// General definitions
#define BAUD                      115200                    // define baud for serial communication

#define BUTTON_RED                10
#define BUTTON_BLACK              11

#define FORWARD                   0
#define BACKWARD                  1

// State Machine States
enum states {EMERGENCY_STOP, STOP, DRIVE_FORWARD, DRIVE_BACKWARD};

// CONFIGURATION NUMBERS
#define BACKWARD_THRESHOLD        30
#define FORWARD_THRESHOLD         50

#define STOP_SPEED                0