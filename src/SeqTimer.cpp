/*!\file SeqTimer.cpp
** \author SMFSW
** \version v2.3
** \date 2015-2017
** \copyright BSD 3-Clause License (c) 2015-2017, SMFSW
** \brief Small piece of sequential Timer class (does not modify hw timers)
** \details The purpose here is to have a small piece of lib being able to manipulate simple timers (does not modify hw timers).
			Keep in mind that this type of timer is not as accurate as a hw timer.
			This library is not intended to be used as a PWM generator for example, but to avoid using delay(s).
			
			Usage:
			Automatic class (can handle timers of 2^32 ms max with 1 ms granularity)
				- init(period) or setPeriod(period) if you want to execute the first step right away
				- in loop: if getTimer() returns true, period has elapsed
			
			Manual class (can handle every uint16 type as time base)
				- init (period, actual time) to set the period and load the compare register with the given actual time
				- in loop: if getTimer(actual time) returns true, period has elapsed
					- possibility to use reloadTimer(actual time) to reload compare register manually (finite running counters)
			
			2 examples included:
			SequentialBlink.ino: a proper way to handle simple timing on a blinking LED
			CascadingTimers.ino: a demonstration how to use own base timers & cascading them to obtain a TimeCounter (not to be used as a real RTC)
			
			Doxygen doc can be generated for the class using doxyfile
			
			Feel free to share your thoughts @ xgarmanboziax@gmail.com about:
				- issues encountered
				- optimisations
				- improvements & new functionalities
**/


#if ARDUINO > 22
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#if defined(DBG_SEQTIMER)
#include <HardwareSerial.h>
#endif

#include "SeqTimer.h"


void SeqTimer::init(const uint32_t Period)
{
	setPeriod(Period);
	reloadTimer(millis());
}

void SeqTimer::init(const uint32_t Period, const uint32_t actTime)
{
	setPeriod(Period);
	reloadTimer(actTime);
}

bool SeqTimer::getTimer(void)
{
	uint32_t tempTime = millis();
	
	if (tempTime - MemTime >= TimerPeriod)
	{
		MemTime = tempTime;
		return true;
	}
	
	return false;
}

bool SeqTimer::getTimer(const uint32_t actTime)
{
	if (actTime - MemTime >= TimerPeriod)
	{
		MemTime = actTime;
		return true;
	}
	
	return false;
}

void SeqTimer::dbgInfo()			// needs SCI initialized in sketch setup
{
	#ifdef DBG_SEQTIMER
	String		dbgInfo = "";
	
	dbgInfo += "!> ";
	dbgInfo += "LastValid: ";
	dbgInfo += MemTime;
	dbgInfo += "\tActual: ";
	dbgInfo += millis();
	dbgInfo += ",\tRate: ";
	dbgInfo += getPeriod();
	dbgInfo += "ms";
	Serial.println(dbgInfo);
	#endif
}

