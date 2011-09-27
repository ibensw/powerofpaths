/*
 * schedule.h
 *
 *  Created on: Sep 26, 2011
 *      Author: ibensw
 */

#ifndef SCHEDULE_H_
#define SCHEDULE_H_

#include "event.h"

namespace pop {

class Schedule {
public:
	inline Schedule(Event* e):
		fE(e)
	{}
	
	inline bool operator<(const Schedule& s) const{
		return fE->getScheduleTime() > s.fE->getScheduleTime();
	}
	
	inline Event* getEvent(){
		return fE;
	}
	
private:
	Event* fE;
};

} /* namespace pop */
#endif /* SCHEDULE_H_ */
