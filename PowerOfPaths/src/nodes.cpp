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

bool RightNode::wasHereFirst(Job* j){
	info_type* ji = dynamic_cast<info_type*>(j->getInfo());

	if (ji->fFirst == 0){
		ji->fFirst = this;
		return false;
	}

	return (ji->fFirst == this);
}

bool RightNode::accept(Job* j){
	if (fCurrent == 0){
		info_type* ji = dynamic_cast<info_type*>(j->getInfo());
		fCurrent = j;
		double len = ji->fLength;
		fRing->getSimulator()->addEvent(new FinishEvent(fRing->getSimulator()->getTime()+len, j));
		return true;
	}
	return false;
}

bool RightNode::pushJob(Job* j){
	if (wasHereFirst(j)){
		return false;
	}

	if (!accept(j)){
		j->forward(fRing->getNode(this->fId+1));
	}

	return true;
}

void RightNode::clearJob(){
	fCurrent = 0;
}

bool SwitchNode::pushJob(Job* j){
	if (wasHereFirst(j)){
		return false;
	}

	if (!accept(j)){
		info_type* ji = dynamic_cast<info_type*>(j->getInfo());
		if (ji->fDirection == 0){
			ji->fDirection = last;
			last*=-1;
		}

		j->forward(fRing->getNode(this->fId + ji->fDirection));
	}
	return true;
}

double RandSwitchNode::v = 0.5;

bool RandSwitchNode::pushJob(Job* j){
	if (wasHereFirst(j)){
		return false;
	}

	if (!accept(j)){
		info_type* ji = dynamic_cast<info_type*>(j->getInfo());
		if (ji->fDirection == 0){
			double rnd = (double)rand() / (double)RAND_MAX;
			ji->fDirection = (rnd < v ? 1 : -1);
		}

		j->forward(fRing->getNode(this->fId + ji->fDirection));
	}
	return true;
}

bool EvenSwitchNode::pushJob(Job* j){
	if (wasHereFirst(j)){
		return false;
	}

	if (!accept(j)){
		info_type* ji = dynamic_cast<info_type*>(j->getInfo());
		if (ji->fDirection == 0){
			ji->fDirection = ((this->getId() % 2 == 1) ? 1 : -1);
		}

		j->forward(fRing->getNode(this->fId + ji->fDirection));
	}
	return true;
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

bool PrimeNode::pushJob(Job* j){
	if (wasHereFirst(j)){
		return false;
	}

	if (!accept(j)){
		info_type* ji = dynamic_cast<info_type*>(j->getInfo());
		if (ji->fDirection == 0){
			ji->fDirection = fPrimes[last];
			++last;
			last%=fPrimesLen;
		}

		j->forward(fRing->getNode(this->fId + ji->fDirection));
	}
	return true;
}

bool RandPrimeNode::pushJob(Job* j){
	if (wasHereFirst(j)){
		return false;
	}

	if (!accept(j)){
		info_type* ji = dynamic_cast<info_type*>(j->getInfo());
		if (ji->fDirection == 0){
			ji->fDirection = fPrimes[rand() % fPrimesLen];
		}

		j->forward(fRing->getNode(this->fId + ji->fDirection));
	}
	return true;
}

bool RandUnvisited::pushJob(Job* j){
	info_type* ji = dynamic_cast<info_type*>(j->getInfo());
	if (ji->visited.count(this->getId())){
		return false;
	}

	if (!accept(j)){
		ji->visited.insert(this->getId());

		if (fRing->getSize() == ji->visited.size()){
			return false;
		}

		unsigned int next;
		if (5*ji->visited.size() > 4*fRing->getSize()){
			unsigned int x = rand() % (fRing->getSize() - ji->visited.size());
			next = x;

			for (set<unsigned int>::iterator it = ji->visited.begin(); it != ji->visited.end(); it++){
				if (*it <= next){
					++next;
				}
			}
		}else{
			do{
				next = rand() % fRing->getSize();
			}while(ji->visited.count(next));
		}

		j->forward(fRing->getNode(next));
	}
	return true;
}

bool ToTopNode::pushJob(Job* j){
	if (wasHereFirst(j)){
		return false;
	}

	if (!accept(j)){
		info_type* ji = dynamic_cast<info_type*>(j->getInfo());
		if (ji->fDirection == 0){
			if (this->getId() > fRing->getSize()/2){
				ji->fDirection = 1;
			}else{
				ji->fDirection = -1;
			}
		}

		j->forward(fRing->getNode(this->fId + ji->fDirection));
	}
	return true;
}

bool RRUnvisited::pushJob(Job* j){
	info_type* ji = dynamic_cast<info_type*>(j->getInfo());
	if (ji->visited.count(this->getId())){
		return false;
	}

	if (!accept(j)){
		ji->visited.insert(this->getId());

		if (fRing->getSize() == ji->visited.size()){
			return false;
		}

		unsigned int next = this->getId() + offset + 1;
		++offset;
		offset%=(fRing->getSize()-1);

		next%=fRing->getSize();
		while (ji->visited.count(next)){
			next++;
			next%=fRing->getSize();
		}

		j->forward(fRing->getNode(next));
	}
	return true;
}
