/*
 * event.h
 *
 *  Created on: Sep 26, 2011
 *      Author: ibensw
 */

#ifndef EVENT_H_
#define EVENT_H_

//#include "simulator.h"

namespace pop {
class Simulator;

class Event {
public:
	inline Event(double scheduled):
		fScheduled(scheduled)
		{}

	inline virtual ~Event(){

	}

	inline double getScheduleTime(){
		return fScheduled;
	}
	
	virtual void run(Simulator* simulator) = 0;
	
protected:
	double fScheduled;
};

} /* namespace pop */
#endif /* EVENT_H_ */
