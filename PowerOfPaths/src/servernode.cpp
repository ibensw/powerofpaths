/*
 * servernode.cpp
 *
 *  Created on: Sep 27, 2011
 *      Author: ibensw
 */

#include "servernode.h"

namespace pop {

ServerNode::ServerNode(unsigned int id, Ring* ring):
	Node(id, ring)
	{}

ServerNode::~ServerNode() {
	// TODO Auto-generated destructor stub
}

} /* namespace pop */
