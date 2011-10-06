/*
 * job.cpp
 *
 *  Created on: Sep 27, 2011
 *      Author: ibensw
 */

#include "job.h"
#include "ring.h"
#include <iostream>
using namespace std;

namespace pop {

unsigned int jobsArrived = 0;
unsigned int jobsFinished = 0;
unsigned int jobsDiscarded = 0;
unsigned int jobsFinishedTotalHops = 0;

Job::Job(JobInfo* ji):
	fStart(-1.0), fFinish(-1.0), fCurrent(0), fHops(-1), fJobInfo(ji)
	{}

Job::~Job() {
	if (fJobInfo){
		delete fJobInfo;
	}
}

void Job::discard(){
	++jobsDiscarded;
	//cout << fCurrent->getId() << "\tJob discarded\t(arrival time: " << fStart << " / #hops: " << fHops << ")" << endl;
	delete this;
}
void Job::finish(double time){
	++jobsFinished;
	jobsFinishedTotalHops+=fHops;
	fFinish = time;
	//cout << fCurrent->getId() << "\tJob finished\t(arrival time: " << fStart << " / finish time: " << fFinish << " / #hops: " << fHops << ")" << endl;
	fCurrent->clearJob();
	delete this;
}

void Job::forward(Node* n){
	if (!fCurrent){
		++jobsArrived;
		fStart = n->getRing()->getSimulator()->getTime();
	}
	++fHops;
	fCurrent = n;
	if (!n->pushJob(this)){
		discard();
	}
}

unsigned int Job::getTotalJobs(){
	return jobsArrived;
}

unsigned int Job::getFinishedJobs(){
	return jobsFinished;
}

unsigned int Job::getDiscardedJobs(){
	return jobsDiscarded;
}

unsigned int Job::getFinishedJobTotalHops(){
	return jobsFinishedTotalHops;
}

} /* namespace pop */
