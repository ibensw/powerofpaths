/*
 * events.h
 *
 *  Created on: Sep 27, 2011
 *      Author: ibensw
 */

#ifndef EVENTS_H_
#define EVENTS_H_

#include "../simulator/event.h"
#include "job.h"

namespace pop {

class ArriveEvent : public Event {
public:
	inline ArriveEvent(double scheduled, Node* n):
		Event(scheduled), first(n)
	{}
	
	inline void run(Simulator* simulator){
		first->pushJob(&j);
	}

private:
	Job j;
	Node* first;
};

} /* namespace pop */
#endif /* EVENTS_H_ */
