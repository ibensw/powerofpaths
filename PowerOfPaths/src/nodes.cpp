/*
 * nodes.cpp
 *
 *  Created on: Sep 27, 2011
 *      Author: ibensw
 */

#include "nodes.h"
#include "ring/job.h"
#include "ring/ring.h"
#include "ring/finishevent.h"
#include <iostream>
using namespace pop;
using namespace std;

RightNode::RightNode(unsigned int id, Ring* ring):
	Node(id, ring), fCurrent(0)
{
	cout << "Created node: " << id << endl;
}

RightNode::~RightNode() {
}


void RightNode::pushJob(Job* j){
	if (j->arrive(this, fRing->getSimulator()->getTime()) == false){
		j->discard();
		return;
	}
	if (fCurrent == 0){
		fCurrent = j;
		fRing->getSimulator()->addEvent(new FinishEvent(fRing->getSimulator()->getTime()+1.0, j));
	}else{
		fRing->getNode(this->fId+1)->pushJob(j);
	}
}

void RightNode::clearJob(){
	fCurrent = 0;
}
