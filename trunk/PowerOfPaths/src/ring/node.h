/*
 * node.h
 *
 *  Created on: Sep 27, 2011
 *      Author: ibensw
 */

#ifndef NODE_H_
#define NODE_H_

namespace pop {
class Ring;
class Job;

class Node {
public:
	Node(unsigned int id, Ring* ring);
	virtual ~Node();
	
	inline unsigned int getId(){
		return fId;
	}
	
	virtual void pushJob(Job* j) = 0;
	virtual void clearJob() = 0;
	
protected:
	unsigned int fId;
	Ring* fRing;
};

} /* namespace pop */
#endif /* NODE_H_ */
