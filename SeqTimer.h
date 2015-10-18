//	SequentialTimer.h - Small piece of sequential Timer class (does not modify hw timers)

#ifndef SeqTimer_h
#define SeqTimer_h

#include <inttypes.h>

//#define		DBG_SEQTIMER


// class containing the required methods for handling sequential timer
class SeqTimer
{
private:
	// Private variables
	// consts
	uint16_t	TimerPeriod;		//!< Timer Period
	// working vars
	uint16_t	MemTime;			//!< Previous timer valid time
	//bool		En;					//!< Module enabled/disable

public:
	void dbgInfo();			// needs SCI initialized in sketch setup
	
	bool tstTimer();					//!< Test timer against actual time in milliseconds
	bool tstTimer(uint16_t actTime);	//!< Tests timer against given time representation (actTime)
	
	void resetCount() __attribute__((always_inline)) {
		MemTime = 0;
	}
	
	void setPeriod(uint16_t Period) __attribute__((always_inline)) {
		TimerPeriod = Period;
	}
	
	uint16_t getPeriod() __attribute__((always_inline)) {
		return TimerPeriod;
	}
	
	/*void enable() __attribute__((always_inline)) {
		En = true;
	}
	
	void disable() __attribute__((always_inline)) {
		En = false;
	}
	
	bool isEnabled() __attribute__((always_inline)) {
		return En;
	}
	
	bool isDisabled() __attribute__((always_inline)) {
		return (En == true ? false : true);
	}*/
};


/*==============================================================================
 * MACROS
 *============================================================================*/

/* public */


#endif /* SeqTimer_h */

