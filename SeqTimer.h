/*!\file SeqTimer.h
** \author SMFSW
** \version v1.0
** \date 2015-2015
** \copyright GNU Lesser General Public License v2.1
** \brief Small piece of sequential Timer class (does not modify hw timers)
** \details The purpose here is to have a small piece of lib being able to manipulate simple timers (does not modify hw timers).
			Keep in mind that this type of timer is not as accurate as a hw timer.
			This library is not intended to be used as a PWM generator for example, but to avoid using delay(s).
			
			Usage: 
			Automatic class (can handle timers of 65,653s max with 1 ms granularity)
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
			
			
			This library is free software; you can redistribute it and/or
			modify it under the terms of the GNU Lesser General Public
			License as published by the Free Software Foundation; either
			version 2.1 of the License, or (at your option) any later version.
			
			This library is distributed in the hope that it will be useful,
			but WITHOUT ANY WARRANTY; without even the implied warranty of
			MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
			Lesser General Public License for more details.
**/

#ifndef SeqTimer_h
#define SeqTimer_h

#include <inttypes.h>

//#define		DBG_SEQTIMER


/*!	\class SeqTimer SeqTimer.h "SeqTimer/SeqTimer.h"
**	\brief Class containing the required methods for handling sequential timer
**/
class SeqTimer
{
private:
	// Private variables
	uint16_t	TimerPeriod;		//!< Timer Period
	uint16_t	MemTime;			//!< Previous timer valid time

public:
	/*!	\brief Sends class informations on SCI when called
	**	\note Symbol DBG_SEQTIMER has to be defined for the function to be verbose
	**	\return nothing
	**/
	void dbgInfo();			// needs SCI initialized in sketch setup
	
	/*!	\brief Initialisation routine
	**	\param [in] Period - Period of the timer (assuming it represents milliseconds to use getTimer without argument)
	**	\return nothing
	**/
	void init(uint16_t Period);
	
	/*!	\brief Initialisation routine
	**	\param [in] Period - Period of the timer (assuming it represents milliseconds to use getTimer without argument)
	**	\param [in] actTime - Actual time in given representation
	**	\return nothing
	**/
	void init(uint16_t Period, uint16_t actTime);
	
	/*!	\brief Test timer period against actual time in milliseconds
	**	\return Test validity
	**	\retval true - Count has reached (or is over) the period set
	**	\retval false - Count has not reached the period set
	**/
	bool getTimer();
	
	/*!	\brief Tests timer against given time representation (actTime)
	**	\param [in] actTime - Actual time in given representation
	**	\return Test validity
	**	\retval true - Count has reached (or is over) the period set
	**	\retval false - Count has not reached the period set
	**/
	bool getTimer(uint16_t actTime);
	
	/*!	\brief Reload last memorised time (manually)
	**	\note Can be useful if using own resetable counter as base time
	**	\param [in] actTime - Actual time in given representation
	**	\return nothing
	**/
	void reloadTimer(uint16_t actTime) __attribute__((always_inline)) {
		MemTime = actTime;
	}
	
	/*!	\brief Set the period of the timer
	**	\param [in] Period - Period of the timer (any uint16 type)
						- assuming it represents milliseconds to use getTimer without argument
							- Timer can be 65,535s max
						- can be own base time coded Period when using getTimer with argument
	**	\return nothing
	**/
	void setPeriod(uint16_t Period) __attribute__((always_inline)) {
		TimerPeriod = Period;
	}
	
	/*!	\brief Get the period of the timer
	**	\return Period value on uint16 type
	**/
	uint16_t getPeriod() __attribute__((always_inline)) {
		return TimerPeriod;
	}
};


#endif /* SeqTimer_h */

