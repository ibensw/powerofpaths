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

Job::Job(JobInfo* ji):
	fStart(-1.0), fFinish(-1.0), fCurrent(0), fHops(-1), fJobInfo(ji)
	{}

Job::~Job() {
	if (fJobInfo){
		delete fJobInfo;
	}
}

void Job::discard(){
	fCurrent->getRing()->jobDiscarded();
	//cout << fCurrent->getId() << "\tJob discarded\t(arrival time: " << fStart << " / #hops: " << fHops << ")" << endl;
	delete this;
}

void Job::finish(double time){
	fCurrent->getRing()->jobFinished(fHops);
	fFinish = time;
	//cout << fCurrent->getId() << "\tJob finished\t(arrival time: " << fStart << " / finish time: " << fFinish << " / #hops: " << fHops << ")" << endl;
	fCurrent->clearJob(this);
	delete this;
}

void Job::forward(Node* n){
	if (!fCurrent){
		n->getRing()->jobCreated();
		fStart = n->getRing()->getSimulator()->getTime();
	}
	++fHops;
	fCurrent = n;
	if (!n->pushJob(this)){
		discard();
	}
}

} /* namespace pop */
