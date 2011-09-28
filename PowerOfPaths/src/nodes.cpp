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
using namespace pop;

RightNode::RightNode(unsigned int id, Ring* ring):
	Node(id, ring), fCurrent(0)
{}

void RightNode::pushJob(Job* j){
	if (j->arrive(this, fRing->getSimulator()->getTime()) == false){
		j->discard();
		return;
	}
	if (fCurrent == 0){
		fCurrent = j;
		double len = dynamic_cast<LengthInfo*>(j->getInfo())->fLength;
		fRing->getSimulator()->addEvent(new FinishEvent(fRing->getSimulator()->getTime()+len, j));
	}else{
		fRing->getNode(this->fId+1)->pushJob(j);
	}
}

void RightNode::clearJob(){
	fCurrent = 0;
}

void SwitchNode::pushJob(Job* j){
	if (j->arrive(this, fRing->getSimulator()->getTime()) == false){
		j->discard();
		return;
	}
	DirectionInfo* info = dynamic_cast<DirectionInfo*>(j->getInfo());
	if (fCurrent == 0){
		fCurrent = j;
		double len = info->fLength;
		fRing->getSimulator()->addEvent(new FinishEvent(fRing->getSimulator()->getTime()+len, j));
	}else{

		if (info->fDirection == 0){
			info->fDirection = last;
			last*=-1;
		}

		fRing->getNode(this->fId+info->fDirection)->pushJob(j);
	}
}
