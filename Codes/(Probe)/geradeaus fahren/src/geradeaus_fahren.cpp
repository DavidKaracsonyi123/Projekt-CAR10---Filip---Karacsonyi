#include <Arduino.h>

// Motor Links
int ML = 10;
int in1 = 9;
int in2 = 8;

// Motor Rechts
int MR = 5;
int in3 = 7;
int in4 = 6;

void setup()
{
    pinMode(ML, OUTPUT);
    pinMode(MR, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
}
void loop()
{
    digitalWrite(in1, LOW); 
    digitalWrite(in2, HIGH);
    analogWrite(ML, 175); 
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(MR, 200); 
    delay(2000);
    digitalWrite(in1, HIGH); 
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, HIGH);
}