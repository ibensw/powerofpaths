#include <iostream>
#include <math.h>
#include <stdlib.h>

#include "ring/ring.h"
#include "ring/arriveevent.h"
#include "nodes.h"
using namespace pop;

double exp_distr(double lambda){
	double r = (double)rand() / (double)RAND_MAX;
	return -lambda * log(r);
}



int main() {
	Ring r(10, RightNode::mkRightNode);
	r.getSimulator()->addEvent(new ArriveEvent(1.0, r.getNode(0)));
	r.getSimulator()->addEvent(new ArriveEvent(1.1, r.getNode(0)));
	r.getSimulator()->addEvent(new ArriveEvent(1.2, r.getNode(0)));
	r.getSimulator()->addEvent(new ArriveEvent(1.3, r.getNode(0)));
	r.getSimulator()->addEvent(new ArriveEvent(1.4, r.getNode(0)));
	r.getSimulator()->addEvent(new ArriveEvent(1.5, r.getNode(0)));
	r.getSimulator()->addEvent(new ArriveEvent(1.6, r.getNode(0)));
	r.getSimulator()->addEvent(new ArriveEvent(1.7, r.getNode(0)));
	r.getSimulator()->addEvent(new ArriveEvent(1.8, r.getNode(0)));
	r.getSimulator()->addEvent(new ArriveEvent(1.9, r.getNode(0)));
	r.getSimulator()->addEvent(new ArriveEvent(1.9, r.getNode(0)));

	r.getSimulator()->run();
	return 0;
}
