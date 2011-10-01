/*
 * nodes.h
 *
 *  Created on: Sep 27, 2011
 *      Author: ibensw
 */

#ifndef NODES_H_
#define NODES_H_

#include "ring/node.h"
#include "ring/ring.h"
#include "ring/job.h"
#include <set>

struct DirectionInfo: public pop::JobInfo{
	inline DirectionInfo(double length):
		pop::JobInfo(length), fDirection(0)
	{}

	short fDirection;
};

struct VisitedInfo: public pop::JobInfo{
	inline VisitedInfo(double length):
		pop::JobInfo(length)
	{}

	std::set<unsigned int> visited;
};

class RightNode: public pop::Node {
public:
	typedef pop::JobInfo info_type;
	static Node* makeNode(unsigned int id, pop::Ring* ring){
		return new RightNode(id, ring);
	}

	RightNode(unsigned int id, pop::Ring* ring);
	
	void pushJob(pop::Job* j);
	void clearJob();
	
protected:
	pop::Job* fCurrent;
};

class SwitchNode: public RightNode {
public:
	typedef DirectionInfo info_type;

	static Node* makeNode(unsigned int id, pop::Ring* ring){
		return new SwitchNode(id, ring);
	}

	inline SwitchNode(unsigned int id, pop::Ring* ring):
			RightNode(id, ring), last(1)
	{}

	void pushJob(pop::Job* j);

protected:
	int last;
};

class RandSwitchNode: public RightNode {
public:
	typedef DirectionInfo info_type;

	static Node* makeNode(unsigned int id, pop::Ring* ring){
		return new RandSwitchNode(id, ring);
	}

	inline RandSwitchNode(unsigned int id, pop::Ring* ring):
			RightNode(id, ring)
	{}

	void pushJob(pop::Job* j);
};

class PrimeNode: public SwitchNode {
public:
	typedef DirectionInfo info_type;

	static void makePrimes(unsigned int size);
	static Node* makeNode(unsigned int id, pop::Ring* ring){
		if (fPrimes == 0){
			makePrimes(ring->getSize());
		}
		return new PrimeNode(id, ring);
	}

	inline PrimeNode(unsigned int id, pop::Ring* ring):
		SwitchNode(id, ring)
	{}

	void pushJob(pop::Job* j);

protected:
	static int* fPrimes;
	static int fPrimesLen;
};

class RandPrimeNode: public PrimeNode{
public:
	typedef DirectionInfo info_type;

	static Node* makeNode(unsigned int id, pop::Ring* ring){
		if (fPrimes == 0){
			makePrimes(ring->getSize());
		}
		return new RandPrimeNode(id, ring);
	}

	RandPrimeNode(unsigned int id, pop::Ring* ring):
		PrimeNode(id, ring)
	{}

	void pushJob(pop::Job* j);
};

class RandUnvisited: public RightNode{
public:
	typedef VisitedInfo info_type;

	static Node* makeNode(unsigned int id, pop::Ring* ring){
		return new RandUnvisited(id, ring);
	}

	RandUnvisited(unsigned int id, pop::Ring* ring):
		RightNode(id, ring)
	{}

	void pushJob(pop::Job* j);
};


#endif /* NODES_H_ */
