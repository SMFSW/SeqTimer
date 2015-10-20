/*
	CascadingTimers.ino
	Sequential clock example. This exemample is only used to demonstrate methods from the lib.
	Of course, do not use this example for a real RTC as it will derive in time in proportion
	of the amount of code build within your project (actual time is checked & updated in the loop).
	
	For testing convenience, the struct initializers are 30 seconds away from a new day, change them at your will.
	
	This example code is in the public domain.
	
	created 18 October 2015
	by SMSFSW
 */

#include <SeqTimer.h>

#define	NB_SEC		60	// Number of seconds in a minute
#define	NB_MIN		60	// Number of minutes in an hour
#define	NB_HOUR		24	// Number of hours in a day

SeqTimer timersec;		// Declare timer for seconds
SeqTimer timermin;		// Declare timer for minutes
SeqTimer timerhour;		// Declare timer for hours

typedef struct {
	unsigned char hours;
	unsigned char minutes;
	unsigned char seconds;
} Time;

Time seqTime = { 23, 59, 30 };

// the setup function runs once when you press reset or power the board
void setup() {
	// initialize timers period
	timersec.init(1000);			// init timer for seconds
	timermin.init(NB_SEC-1, 0);		// init timer minutes (assuming timersec is used as base for this one)
	timerhour.init(NB_MIN-1, 0);	// init timer hours (assuming timermin is used as the base for this one)

	// initialize serial
	Serial.begin(9600);
	//while (!Serial) { };			// wait for serial port to connect. Needed for Leonardo only
}

// the loop function runs over and over again forever
void loop() {
	
	if (timersec.getTimer())							// Test seconds
	{
		if (timermin.getTimer(seqTime.seconds))			// Test minutes
		{
			if (timerhour.getTimer(seqTime.minutes))	// Test hours
			{
				// If hours overflow, set back to 0
				if (++seqTime.hours >= NB_HOUR)	{ seqTime.hours = 0; }
			}
			
			// If minutes overflow, set back to 0
			if (++seqTime.minutes >= NB_MIN)
			{
				seqTime.minutes = 0;
				timerhour.reloadTimer(seqTime.minutes);	// Reload counter for external base time use
			}
		}
		
		// If seconds overflow, set back to 0
		if (++seqTime.seconds >= NB_SEC)
		{
			seqTime.seconds = 0;
			timermin.reloadTimer(seqTime.seconds);		// Reload counter for external base time use
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