/*
 * servernode.h
 *
 *  Created on: Sep 27, 2011
 *      Author: ibensw
 */

#ifndef SERVERNODE_H_
#define SERVERNODE_H_

#include "ring/node.h"
#include "ring/ring.h"

namespace pop {

class ServerNode: public Node {
public:
	ServerNode(unsigned int id, Ring* ring);
	virtual ~ServerNode();
};

} /* namespace pop */
#endif /* SERVERNODE_H_ */
