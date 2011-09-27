/*
 * finishevent.h
 *
 *  Created on: Sep 27, 2011
 *      Author: ibensw
 */

#ifndef FINISHEVENT_H_
#define FINISHEVENT_H_

#include "../simulator/simulator.h"
#include "../simulator/event.h"
#include "job.h"

namespace pop {

class FinishEvent: public Event {
public:
	inline FinishEvent(double scheduled, Job* job):
		Event(scheduled), j(job)
	{}
	
	inline void run(Simulator* simulator){
		j->finish(simulator->getTime());
	}
	
private:
	Job* j;
};

} /* namespace pop */
#endif /* FINISHEVENT_H_ */
