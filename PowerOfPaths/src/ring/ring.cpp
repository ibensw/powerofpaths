/*
 * ring.cpp
 *
 *  Created on: Sep 27, 2011
 *      Author: ibensw
 */

#include "ring.h"

namespace pop {

Ring::Ring(unsigned int size, unsigned int nodesize, Node* (*mkNode)(unsigned int i, Ring* r, unsigned int ns)):
	fSize(size),
	fRing(new Node*[size]),
	jobsTotal(0), jobsFinished(0), jobsDiscarded(0), jobsFinishedTotalHops(0)
{
	for (unsigned int i = 0; i < size; ++i){
		fRing[i] = mkNode(i, this, nodesize);
	}
}

Ring::~Ring() {
	for (unsigned int i = 0; i < fSize; ++i){
		delete fRing[i];
	}
	delete[] fRing;
}

} /* namespace pop */
