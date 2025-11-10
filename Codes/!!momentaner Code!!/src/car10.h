#ifndef CAR10_H
#define CAR10_H

// Motor Pins
extern int ML;
extern int in1;
extern int in2;
extern int MR;
extern int in3;
extern int in4;

extern const int startpin;
extern const int stoppin;
extern bool fahren;

void motorSetup();
void moveForward();
void stopMotors();
void startCar();
void stopCar();

#endif
