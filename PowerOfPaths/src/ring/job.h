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

class JobInfo {
public:
	virtual ~JobInfo(){

	}
};

class Job {
public:
	Job(JobInfo* ji);
	virtual ~Job();
	
	inline Node* getCurrentNode(){
		return fCurrent;
	}

	inline JobInfo* getInfo(){
		return fJobInfo;
	}

	virtual bool arrive(Node* n, double time);
	virtual void finish(double time);
	virtual void discard();
	
	static unsigned int getArrivedJobs();
	static unsigned int getDiscardedJobs();
	static unsigned int getFinishedJobs();
	static unsigned int getFinishedJobTotalHops();

private:
	double fStart;
	double fFinish;
	Node* fCurrent;
	Node* fFirst;
	unsigned int fHops;
	JobInfo* fJobInfo;
};

} /* namespace pop */
#endif /* JOB_H_ */
