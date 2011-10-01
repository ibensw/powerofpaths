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

//#include <iostream>

namespace pop {

class Ring {
public:
	Ring(unsigned int size, Node* (*mkNode)(unsigned int i, Ring* r));
	virtual ~Ring();
	
	inline unsigned int getSize(){
		return fSize;
	}
	
	inline Node* getNode(int id){
		//std::cout << "id: " << id << " = " << (id + fSize) % fSize << std::endl;
		return fRing[(id + fSize) % fSize];
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
