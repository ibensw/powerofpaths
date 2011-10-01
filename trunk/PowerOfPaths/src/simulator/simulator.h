/*
 * simulator.h
 *
 *  Created on: Sep 26, 2011
 *      Author: ibensw
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <queue>
#include "event.h"
#include "schedule.h"

namespace pop {

class Simulator {
public:
	Simulator();
	virtual ~Simulator();
	
	void run();
	void run(int infointerval);
	
	inline double getTime(){
		return fNow;
	}
	
	inline unsigned int getPendingEvents(){
		return fPending.size();
	}
	
	void addEvent(Event* e);
	
private:
	std::priority_queue<Schedule> fPending;
	double fNow;
};

} /* namespace pop */
#endif /* SIMULATOR_H_ */
