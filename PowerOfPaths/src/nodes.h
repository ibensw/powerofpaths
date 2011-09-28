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

struct LengthInfo: public pop::JobInfo{
	inline LengthInfo(double length):
		fLength(length)
	{}

	double fLength;
};

struct DirectionInfo: public LengthInfo{
	inline DirectionInfo(double length):
		LengthInfo(length), fDirection(0)
	{}

	short fDirection;
};

class RightNode: public pop::Node {
public:
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
	static Node* makeNode(unsigned int id, pop::Ring* ring){
		return new SwitchNode(id, ring);
	}

	inline SwitchNode(unsigned int id, pop::Ring* ring):
			RightNode(id, ring), last(1)
	{}

	void pushJob(pop::Job* j);

private:
	short last;
};


#endif /* NODES_H_ */
