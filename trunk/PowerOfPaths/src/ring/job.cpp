/*
 * job.cpp
 *
 *  Created on: Sep 27, 2011
 *      Author: ibensw
 */

#include "job.h"
#include <iostream>
using namespace std;

namespace pop {

unsigned int jobsArrived = 0;
unsigned int jobsFinished = 0;
unsigned int jobsDiscarded = 0;
unsigned int jobsFinishedTotalHops = 0;

Job::Job(JobInfo* ji):
	fStart(-1.0), fFinish(-1.0), fCurrent(0), fFirst(0), fHops(-1), fJobInfo(ji)
	{}

Job::~Job() {
	if (fJobInfo){
		delete fJobInfo;
	}
}

bool Job::arrive(Node* n, double time){
	if (n == fFirst){
		return false;
	}

	if (fCurrent == 0){
		++jobsArrived;
		//cout << n->getId() << "\tJob arrived\t(arrival time: " << time << ")" << endl;
		fStart=time;
		fFirst=n;
	}else{
		//cout << n->getId() << "\tJob redirected\t(arrival time: " << time << ")" << endl;
	}
	fCurrent = n;
	++fHops;
	return true;
}

void Job::finish(double time){
	++jobsFinished;
	jobsFinishedTotalHops+=fHops;
	fFinish = time;
	//cout << fCurrent->getId() << "\tJob finished\t(arrival time: " << fStart << " / finish time: " << fFinish << " / #hops: " << fHops << ")" << endl;
	fCurrent->clearJob();
}

void Job::discard(){
	++jobsDiscarded;
	//cout << fCurrent->getId() << "\tJob discarded\t(arrival time: " << fStart << " / #hops: " << fHops << ")" << endl;
	delete this;
}

unsigned int Job::getArrivedJobs(){
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
