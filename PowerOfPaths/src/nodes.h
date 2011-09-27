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

class RightNode: public pop::Node {
public:
	static Node* mkRightNode(unsigned int id, pop::Ring* ring){
		return new RightNode(id, ring);
	}

	RightNode(unsigned int id, pop::Ring* ring);
	virtual ~RightNode();
	
	void pushJob(pop::Job* j);
	void clearJob();
	
private:
	pop::Job* fCurrent;
};

#endif /* NODES_H_ */
