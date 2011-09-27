/*
 * job.h
 *
 *  Created on: Sep 27, 2011
 *      Author: ibensw
 */

#ifndef JOB_H_
#define JOB_H_

#include "node.h"

namespace pop {

class Job {
public:
	Job();
	virtual ~Job();
	
	inline Node* getCurrentNode(){
		return fCurrent;
	}

	virtual bool arrive(Node* n, double time);
	virtual void finish(double time);
	virtual void discard();
	
private:
	double fStart;
	double fFinish;
	Node* fCurrent;
	Node* fFirst;
	unsigned int fHops;
};

} /* namespace pop */
#endif /* JOB_H_ */
