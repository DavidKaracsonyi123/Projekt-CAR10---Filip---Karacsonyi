#include <Arduino.h>

// Motor Links
int ML = 10;
int in1 = 9;
int in2 = 8;

// Motor Rechts
int MR = 5;
int in3 = 7;
int in4 = 6;

// Sensor Pins
int sensorMitte = A0;
int sensorLinks = A1;
int sensorRechts = A2;

// Schwellenwert für Hindernis-Erkennung (angepasst je nach Bedarf)
int schwellenwert = 200;  // Anpassen je nach den gemessenen ADC-Werten

// Funktionsprototypen
void geradeausFahren();
void weicheNachLinks();
void weicheNachRechts();

void setup()
{
  // Pin-Modi setzen
  pinMode(ML, OUTPUT);
  pinMode(MR, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Sensor Pins setzen
  pinMode(sensorMitte, INPUT);
  pinMode(sensorLinks, INPUT);
  pinMode(sensorRechts, INPUT);
}

void loop()
{
  int wertMitte = analogRead(sensorMitte);  // Liest den Wert des Mittelsensors
  int wertLinks = analogRead(sensorLinks);  // Liest den Wert des Linksensors
  int wertRechts = analogRead(sensorRechts);  // Liest den Wert des Rechtsensors

  // Wenn beide, Mittel- und Rechtesensor, ein Hindernis erkennen, nach links ausweichen
  if (wertMitte > schwellenwert && wertRechts > schwellenwert)
  {
    weicheNachLinks();
  }
  // Wenn beide, Mittel- und Linksensor, ein Hindernis erkennen, nach rechts ausweichen
  else if (wertMitte > schwellenwert && wertLinks > schwellenwert)
  {
    weicheNachRechts();
  }
  // Wenn kein Hindernis erkannt wird, geradeaus fahren
  else
  {
    geradeausFahren();
  }

  delay(100);  // Kurze Verzögerung für stabile Sensorabfrage
}

void geradeausFahren()
{
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH);
  analogWrite(ML, 175);  // Geschwindigkeit des linken Motors
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(MR, 200);  // Geschwindigkeit des rechten Motors
}

void weicheNachLinks()
{
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH);
  analogWrite(ML, 100);  // Verringert die Geschwindigkeit für den linken Motor
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(MR, 200);  // Normalgeschwindigkeit für den rechten Motor
  delay(500);  // Für eine halbe Sekunde nach links ausweichen
}

void weicheNachRechts()
{
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH);
  analogWrite(ML, 200);  // Normalgeschwindigkeit für den linken Motor
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(MR, 100);  // Verringert die Geschwindigkeit für den rechten Motor
  delay(500);  // Für eine halbe Sekunde nach rechts ausweichen
}
