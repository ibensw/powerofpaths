#include <iostream>
#include <math.h>
#include <stdlib.h>

#include "ring/ring.h"
#include "ring/job.h"
#include "ring/arriveevent.h"
#include "nodes.h"
using namespace pop;
using namespace std;

double exp_distr(double lambda){
	double r = (double)rand() / (double)RAND_MAX;
	return -lambda * log(r);
}

template <class INFO>
void fillEvents(double time, double interarr, double joblen, Ring* r){
	double t;
	double l;
	Node* n;
	for (unsigned int i = 0; i < r->getSize(); ++i){
		n=r->getNode(i);
		t = 0.0;
		while (t < time){
			t+=exp_distr(interarr);
			l=exp_distr(joblen);
			r->getSimulator()->addEvent(new ArriveEvent(t, new Job(new INFO(l)), n));
		}
	}
}

int main() {
	Ring r(10, SwitchNode::makeNode);
	fillEvents<DirectionInfo>(60*60*24, 10.0, 1.0, &r);

	r.getSimulator()->run();

	cout << "Total jobs:\t" << Job::getArrivedJobs() << endl;
	cout << "Finished jobs:\t" << Job::getFinishedJobs() << endl;
	cout << "Discarded jobs:\t" << Job::getDiscardedJobs() << endl;
	cout << "Total hops:\t" << Job::getFinishedJobTotalHops() << endl;
	cout << "Hops/job:\t" << (double)Job::getFinishedJobTotalHops()/Job::getFinishedJobs() << endl;
	cout << "Success ratio:\t" << (100.0 * Job::getFinishedJobs()) / Job::getArrivedJobs() << "%" << endl;

	return 0;
}
