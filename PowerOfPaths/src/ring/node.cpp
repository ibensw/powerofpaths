/*
 * node.cpp
 *
 *  Created on: Sep 27, 2011
 *      Author: ibensw
 */

#include "node.h"

namespace pop {

Node::Node(unsigned int id, Ring* ring):
	fId(id), fRing(ring)
	{}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

} /* namespace pop */
