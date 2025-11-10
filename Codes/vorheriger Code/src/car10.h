/**
 * Autonom Driving Car - CAR-10
 * Algorithm to navigate through the race track as fast as possible
 * (C) 2025 David Karacsonyi, Oskar Filip
 *
 *	file	car10.h
 */

#ifndef CAR10_H
#define CAR10_H

// Motorsteuerpins für L298N Motor Shield
#define IN1                        9   // Steuerpin 1 für linken Motor
#define IN2                        8   // Steuerpin 2 für linken Motor
#define IN3                        7   // Steuerpin 3 für rechten Motor
#define IN4                        6   // Steuerpin 4 für rechten Motor
#define ENA                        10  // PWM für linken Motor
#define ENB                        5   // PWM für rechten Motor

// Schwellenwert für Hinderniserkennung
#define FORWARD_THRESHOLD         50  // Schwellenwert für die Frontsensoren (40 cm -> ADC-Wert ca. 300-400)

// Funktionserklärungen
void init_motors();
void drive_forward();
void stop_motors();
void turn_left();
void turn_right();
void init_uart();

#endif
