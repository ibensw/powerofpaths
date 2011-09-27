/*
 * ring.h
 *
 *  Created on: Sep 27, 2011
 *      Author: ibensw
 */

#ifndef RING_H_
#define RING_H_

#include "node.h"
#include "../simulator/simulator.h"

namespace pop {

class Ring {
public:
	Ring(unsigned int size, Node* (*mkNode)(unsigned int i, Ring* r));
	virtual ~Ring();
	
	inline unsigned int getSize(){
		return fSize;
	}
	
	inline Node* getNode(unsigned int id){
		return fRing[id % fSize];
	}
	
	inline Simulator* getSimulator(){
		return &fSimulator;
	}
	
private:
	unsigned int fSize;
	Node** fRing;
	Simulator fSimulator;
};

} /* namespace pop */
#endif /* RING_H_ */
