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
		fLength(length), fDirection(0), fFirst(0)
	{}

	double fLength;
	short fDirection;
	pop::Node* fFirst;
};

struct VisitedInfo: public DirectionInfo{
	inline VisitedInfo(double length):
		DirectionInfo(length)
	{}

	std::set<unsigned int> visited;
};

class RightNode: public pop::Node {
public:
	typedef DirectionInfo info_type;

	RightNode(unsigned int id, pop::Ring* ring);
	
	virtual ~RightNode(){}

	bool pushJob(pop::Job* j);
	void clearJob();
	
	bool wasHereFirst(pop::Job* j);
	bool accept(pop::Job* j);

protected:
	pop::Job* fCurrent;
};

class SwitchNode: public RightNode {
public:
	typedef DirectionInfo info_type;

	inline SwitchNode(unsigned int id, pop::Ring* ring):
			RightNode(id, ring), last(1)
	{}

	bool pushJob(pop::Job* j);

protected:
	int last;
};

class RandSwitchNode: public RightNode {
public:
	typedef DirectionInfo info_type;

	inline RandSwitchNode(unsigned int id, pop::Ring* ring):
			RightNode(id, ring)
	{}

	bool pushJob(pop::Job* j);
};

class PrimeNode: public SwitchNode {
public:
	typedef DirectionInfo info_type;

	static void makePrimes(unsigned int size);

	inline PrimeNode(unsigned int id, pop::Ring* ring):
		SwitchNode(id, ring)
	{
		if (fPrimes == 0){
			makePrimes(ring->getSize());
		}
	}

	bool pushJob(pop::Job* j);

protected:
	static int* fPrimes;
	static int fPrimesLen;
};

class RandPrimeNode: public PrimeNode{
public:
	typedef DirectionInfo info_type;

	RandPrimeNode(unsigned int id, pop::Ring* ring):
		PrimeNode(id, ring)
	{
		if (fPrimes == 0){
			makePrimes(ring->getSize());
		}
	}

	bool pushJob(pop::Job* j);
};

class RandUnvisited: public RightNode{
public:
	typedef VisitedInfo info_type;

	RandUnvisited(unsigned int id, pop::Ring* ring):
		RightNode(id, ring)
	{}

	bool pushJob(pop::Job* j);
};

class ToTopNode: public RightNode{
public:
	typedef DirectionInfo info_type;

	ToTopNode(unsigned int id, pop::Ring* ring):
		RightNode(id, ring)
	{}

	bool pushJob(pop::Job* j);
};


#endif /* NODES_H_ */
