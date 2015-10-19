/*
  SequentialBlink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 18 October 2015
  by SMSFSW
 */

#include <SeqTimer.h>

SeqTimer timer;				// Declare timer
boolean  LEDState = LOW;	// State HIGH/LOW

// the setup function runs once when you press reset or power the board
void setup() {
	// initialize digital pin 13 as an output.
	pinMode(13, OUTPUT);

	// initialize the timer period
	timer.init(1000);
}

// the loop function runs over and over again forever
void loop() {
	if (timer.getTimer() == true)
	{
		LEDState = !LEDState;		// Change LED
		digitalWrite(13, LEDState);	// turn the LED into LEDState
	}
}
