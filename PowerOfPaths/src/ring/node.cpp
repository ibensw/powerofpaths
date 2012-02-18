/*
 * node.cpp
 *
 *  Created on: Sep 27, 2011
 *      Author: ibensw
 */

#include "node.h"

namespace pop {

Node::Node(unsigned int id, Ring* ring, unsigned int size):
	fId(id), fRing(ring), fSize(size)
	{}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

} /* namespace pop */
