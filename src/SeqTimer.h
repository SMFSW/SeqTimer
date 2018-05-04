/*!\file SeqTimer.h
** \author SMFSW
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
	uint32_t	TimerPeriod;		//!< Timer Period
	uint32_t	MemTime;			//!< Previous timer valid time

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
	void init(const uint32_t Period);
	
	/*!	\brief Initialisation routine
	**	\param [in] Period - Period of the timer (assuming it represents milliseconds to use getTimer without argument)
	**	\param [in] actTime - Actual time in given representation
	**	\return nothing
	**/
	void init(const uint32_t Period, const uint32_t actTime);
	
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
	bool getTimer(const uint32_t actTime);
	
	/*!	\brief Reload last memorised time (manually)
	**	\note Can be useful if using own resetable counter as base time
	**	\param [in] actTime - Actual time in given representation
	**	\return nothing
	**/
	void reloadTimer(const uint32_t actTime) __attribute__((always_inline)) {
		MemTime = actTime;
	}
	
	/*!	\brief Set the period of the timer
	**	\param [in] Period - Period of the timer (any uint16 type)
						- assuming it represents milliseconds to use getTimer without argument
							- Timer can be 65,535s max
						- can be own base time coded Period when using getTimer with argument
	**	\return nothing
	**/
	void setPeriod(const uint32_t Period) __attribute__((always_inline)) {
		TimerPeriod = Period;
	}
	
	/*!	\brief Get the period of the timer
	**	\return Period value on uint16 type
	**/
	uint32_t getPeriod(void) __attribute__((always_inline)) {
		return TimerPeriod;
	}
};


#endif /* SeqTimer_h */

