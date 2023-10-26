/* 
 * Project Grove UltraSonic Sensor
 * Author: Brian Rashap
 * Date: 26-OCT-2023
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "Grove-Ultrasonic-Ranger.h"
SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);
Ultrasonic ultrasonic(D19);

int RangeInCentimeters;

void setup() {
	Serial.begin(9600);
  waitFor(Serial.isConnected,10000);
}

void loop() {
	RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
	Serial.printf("The distance to obstacles in front is: %i\n",RangeInCentimeters);	
	delay(250);
}