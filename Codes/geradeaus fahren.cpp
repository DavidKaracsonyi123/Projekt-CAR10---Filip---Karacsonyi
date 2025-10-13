#include <Arduino.h>
// Gleichstrommotor 1
int GSM1 = 10;
int in1 = 9;
int in2 = 8;
// Gleichstrommotor 2
int GSM2 = 5;
int in3 = 7;
int in4 = 6;
void setup()
{
pinMode(GSM1, OUTPUT);
pinMode(GSM2, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
}
void loop()
{
digitalWrite(in1, HIGH); // Motor 1 beginnt zu rotieren
digitalWrite(in2, LOW);
analogWrite(GSM1, 175); // rechts soll mit der Geschwindigkeit "200" (m
digitalWrite(in3, LOW); // Motor 2 beginnt zu rotieren
digitalWrite(in4, HIGH);
analogWrite(GSM2, 200); // links 2 soll ebenfalls mit der Geschwindigkei
delay(2000);
digitalWrite(in1, HIGH); // Durch die Veränderung von HIGH auf LOW (bzw.
digitalWrite(in2, HIGH);
digitalWrite(in3, HIGH);
digitalWrite(in4, HIGH);

}