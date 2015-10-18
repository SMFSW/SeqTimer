/*
	SeqTimer.cpp - Small piece of sequential Timer class (does not modify hw timers)
	Copyright (c) 2015-2015 SMFSW.
	
	Usage: Declare class / Set Period / Test Timer
	setPeriod : set the period of the timer (assuming it is milliseconds if you want to use tstTimer without argument)
				- you can specify 1 uint16_t with period in your own base time
	tstTimer :	- without argument: compares against Period given in setPeriod 
				- you can specify 1 uint16_t to compare against your own base time
	
	The purpose here is to have a small piece of lib being able to manipulate simple timers (does not modify hw timers).
	Keep in mind that this type of timer is not as accurate as a hw timer.
	This library is not intended to be used as a PWM generator for example, just to avoid using delay(s).
	
	Feel free to share your thoughts @ xgarmanboziax@gmail.com about:
		- issues encountered
		- optimisations
		- improvements & new functionalities


	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.
*/
 
/*
	18 October 2015		- First release
*/

#if ARDUINO > 22
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#ifdef DBG_SEQTIMER
#include <HardwareSerial.h>
#endif

#include "SeqTimer.h"


bool SeqTimer::tstTimer()
{
	uint16_t	tempTime = millis();
	
	if ((tempTime - MemTime) >= TimerPeriod)
	{
		MemTime = tempTime;
		return true;
	}
	
	return false;
}

bool SeqTimer::tstTimer(uint16_t actTime)
{
	if ((actTime - MemTime) >= TimerPeriod)
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