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
	inline JobInfo(){}

	virtual ~JobInfo(){}
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

	void forward(Node* n);
	void finish(double time);
	void discard();
	
	static unsigned int getTotalJobs();
	static unsigned int getDiscardedJobs();
	static unsigned int getFinishedJobs();
	static unsigned int getFinishedJobTotalHops();

private:
	double fStart;
	double fFinish;
	Node* fCurrent;
	unsigned int fHops;
	JobInfo* fJobInfo;
};

} /* namespace pop */
#endif /* JOB_H_ */
