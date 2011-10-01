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
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>

using namespace pop;
using namespace std;

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
		double len = j->getInfo()->getLength();
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
		double len = j->getInfo()->getLength();
		fRing->getSimulator()->addEvent(new FinishEvent(fRing->getSimulator()->getTime()+len, j));
	}else{

		if (info->fDirection == 0){
			info->fDirection = last;
			last*=-1;
		}

		fRing->getNode(this->fId + info->fDirection)->pushJob(j);
	}
}

void RandSwitchNode::pushJob(Job* j){
	if (j->arrive(this, fRing->getSimulator()->getTime()) == false){
		j->discard();
		return;
	}
	DirectionInfo* info = dynamic_cast<DirectionInfo*>(j->getInfo());
	if (fCurrent == 0){
		fCurrent = j;
		double len = j->getInfo()->getLength();
		fRing->getSimulator()->addEvent(new FinishEvent(fRing->getSimulator()->getTime()+len, j));
	}else{

		if (info->fDirection == 0){
			info->fDirection = (2*(rand() % 2))-1;
		}

		fRing->getNode(this->fId + info->fDirection)->pushJob(j);
	}
}

int* PrimeNode::fPrimes = 0;
int PrimeNode::fPrimesLen = 0;

unsigned int gcd(unsigned int a, unsigned b){
	unsigned int t;
	while(b){
		t=b;
		b=a%b;
		a=t;
	}
	return a;
}

void PrimeNode::makePrimes(unsigned int size){
	vector<unsigned int> primes;
	for (unsigned int i = 1; i < size; ++i){
		if (gcd(size, i) == 1){
			cout << "RelPrime: " << i << endl;
			primes.push_back(i);
		}
	}
	fPrimesLen = primes.size();
	fPrimes = new int[fPrimesLen];
	memcpy(fPrimes, primes.data(), fPrimesLen * sizeof(unsigned int));
}

void PrimeNode::pushJob(Job* j){
	if (j->arrive(this, fRing->getSimulator()->getTime()) == false){
		j->discard();
		return;
	}
	DirectionInfo* info = dynamic_cast<DirectionInfo*>(j->getInfo());
	if (fCurrent == 0){
		fCurrent = j;
		double len = j->getInfo()->getLength();
		fRing->getSimulator()->addEvent(new FinishEvent(fRing->getSimulator()->getTime()+len, j));
	}else{

		if (info->fDirection == 0){
			info->fDirection = fPrimes[last];
			++last;
			last%=fPrimesLen;
		}

		fRing->getNode(this->fId + info->fDirection)->pushJob(j);
	}
}

void RandPrimeNode::pushJob(Job* j){
	if (j->arrive(this, fRing->getSimulator()->getTime()) == false){
		j->discard();
		return;
	}
	DirectionInfo* info = dynamic_cast<DirectionInfo*>(j->getInfo());
	if (fCurrent == 0){
		fCurrent = j;
		double len = j->getInfo()->getLength();
		fRing->getSimulator()->addEvent(new FinishEvent(fRing->getSimulator()->getTime()+len, j));
	}else{

		if (info->fDirection == 0){
			info->fDirection = fPrimes[rand() % fPrimesLen];
		}

		fRing->getNode(this->fId + info->fDirection)->pushJob(j);
	}
}

void RandUnvisited::pushJob(Job* j){
	VisitedInfo* info = dynamic_cast<VisitedInfo*>(j->getInfo());
	if (j->arrive(this, fRing->getSimulator()->getTime()) == false || info->visited.count(this->getId())){
		j->discard();
		return;
	}
	if (fCurrent == 0){
		fCurrent = j;
		double len = j->getInfo()->getLength();
		fRing->getSimulator()->addEvent(new FinishEvent(fRing->getSimulator()->getTime()+len, j));
	}else{
		info->visited.insert(this->getId());

		if (fRing->getSize() == info->visited.size()){
			this->pushJob(j);
			return;
		}

		/*unsigned int x = rand() % (fRing->getSize() - info->visited.size());
		unsigned int id = x;

		for (set<unsigned int>::iterator it = info->visited.begin(); it != info->visited.end(); it++){
			if (*it <= id){
				++id;
			}
		}

		if (info->visited.count(id)){
			cerr << "ERROR: Chose an id that has been visited already!" << endl;
		}*/

		unsigned int x;
		do{
			x = rand() % fRing->getSize();
		}while(info->visited.count(x));

		fRing->getNode(x)->pushJob(j);
	}
}
