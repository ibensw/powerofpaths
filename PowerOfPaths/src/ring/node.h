/*
 * node.h
 *
 *  Created on: Sep 27, 2011
 *      Author: ibensw
 */

#ifndef NODE_H_
#define NODE_H_

#include <set>

namespace pop {
class Ring;
class Job;

class Node {
public:
	Node(unsigned int id, Ring* ring, unsigned int size = 1);
	virtual ~Node();
	
	inline unsigned int getId() const{
		return fId;
	}
	
	inline Ring* getRing() const {
		return fRing;
	}

	inline unsigned int getTotalSize() const{
		return fSize;
	}

	inline unsigned int getSize() const{
		return fCurrents.size();
	}

	inline bool isBusy() const{
		return fCurrents.size() == fSize;
	}

	virtual bool pushJob(Job* j) = 0;
	virtual void clearJob(Job* j) = 0;
	
protected:
	unsigned int fId;
	Ring* fRing;
	std::set<Job*> fCurrents;
	unsigned int fSize;
};

} /* namespace pop */
#endif /* NODE_H_ */
