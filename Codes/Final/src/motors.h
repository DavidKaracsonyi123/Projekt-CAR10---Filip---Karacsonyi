// PIN definitions
#define MOTOR_RIGHT_SPEED         5   // PWM Timer0 // ENB
#define MOTOR_LEFT_SPEED          6   // PWM Timer0 // ENA

#define MOTOR_RIGHT_FORWARD       4 // IN3
#define MOTOR_RIGHT_BACKWARD      9 // IN4
#define MOTOR_LEFT_FORWARD        7 // IN2
#define MOTOR_LEFT_BACKWARD       8 // IN1

void init_motors();
void stop();
