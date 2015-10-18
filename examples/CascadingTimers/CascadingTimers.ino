/*
	CascadingTimers.ino
	Sequential clock example. This exemample is only used to demonstrate methods from the lib.
	Of course, do not use this example for an RTC as it will derive in time in proportion
	of the amount of code build within your project (actual time is checked & updated in the loop).
	
	For convenience testing, the struct initializers are 30 seconds from a new day. Change them at your will.
	
	This example code is in the public domain.
	
	created 18 October 2015
	by SMSFSW
 */

#include "SeqTimer.h"

#define	NB_SEC	60		// Number of seconds in a minute
#define	NB_MIN	60		// Number of minutes in an hour
#define	NB_HOUR	24		// Number of hours in a day

SeqTimer timersec;		// Declare timer for seconds
SeqTimer timermin;		// Declare timer for minutes
SeqTimer timerhour;		// Declare timer for hours

struct {
	unsigned char hours = 23;
	unsigned char minutes = 59;
	unsigned char seconds = 30;
} seqTime;


// the setup function runs once when you press reset or power the board
void setup() {
	// initialize timers period
	timersec.setPeriod(1000);	// init timer for seconds
	timermin.setPeriod(NB_SEC);	// init timer minutes (assuming we'll use timersec as the base for this one)
	timerhour.setPeriod(NB_MIN);	// init timer hours (assuming we'll use timermin as the base for this one)

	// initialize serial
	Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
	if (timersec.tstTimer())
	{
		if (++seqTime.seconds >= NB_SEC)
		{
			seqTime.seconds = 0;
			//timersec.resetCount();	// No reset count for basic class (otherwise, the timer will be valid next time tested)
		}
		
		if (timermin.tstTimer(seqTime.seconds-1))
		{
			if (++seqTime.minutes >= NB_MIN)	// Trick to trigger Timers if external base time reloads the counter to default value
			{
				seqTime.minutes = 0;
				timermin.resetCount();	// Reset count for external base time use
			}
			
			if (timerhour.tstTimer(seqTime.minutes-1))	// Trick to trigger Timers if external base time reloads the counter to default value
			{
				if (++seqTime.hours >= NB_HOUR)
				{
					seqTime.hours = 0;
					timerhour.resetCount();	// Reset count for external base time use
				}
			}
		}
		
		// Send time to Rs every second
		Serial.print(seqTime.hours);
		Serial.print("H  ");
		Serial.print(seqTime.minutes);
		Serial.print("m  ");
		Serial.print(seqTime.seconds);
		Serial.println("s");
	}
}