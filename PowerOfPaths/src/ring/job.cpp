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

Job::Job():
	fStart(-1.0), fFinish(-1.0), fCurrent(0), fFirst(0), fHops(-1)
	{}

Job::~Job() {
	// TODO Auto-generated destructor stub
}

bool Job::arrive(Node* n, double time){
	if (n == fFirst){
		return false;
	}

	if (fCurrent == 0){
		fStart=time;
		fFirst=n;
	}
	fCurrent = n;
	++fHops;
	return true;
}

void Job::finish(double time){
	fFinish = time;
	cout << "Job finished (arrival time: " << fStart << " / finish time: " << fFinish << " / #hops: " << fHops << ")" << endl;
	fCurrent->clearJob();
}

void Job::discard(){
	cout << "Job discarded (arrival time: " << fStart << " / #hops: " << fHops << ")" << endl;
}

} /* namespace pop */
