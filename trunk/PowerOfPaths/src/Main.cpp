#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "ring/ring.h"
#include "ring/job.h"
#include "ring/arriveevent.h"
#include "nodes.h"
#include "configuration.h"
using namespace pop;
using namespace std;

double exp_distr(double lambda){
	double r = (double)rand() / (double)RAND_MAX;
	return -lambda * log(r);
}

void fillEvents(Configuration c, Ring* r){
	double t;
	double l;
	Node* n;
	for (unsigned int i = 0; i < r->getSize(); ++i){
		n=r->getNode(i);
		t = 0.0;
		while (t < c.length){
			t+=exp_distr(c.arrival);
			l=exp_distr(c.joblength);
			r->getSimulator()->addEvent(new ArriveEvent(t, new Job(c.makeInfoFunction(l)), n));
		}
	}
}


int main(int argc, char** argv) {
	Configuration c(argc, argv);

	Ring r(c.nodes, c.makeNodeFunction);
	fillEvents(c, &r);

	if (c.progressinterval <= 0){
		r.getSimulator()->run();
	}else{
		r.getSimulator()->run(c.progressinterval);
	}

	cout << "Total jobs:\t\t" << Job::getTotalJobs() << endl;
	cout << "Finished jobs:\t\t" << Job::getFinishedJobs() << endl;
	cout << "Discarded jobs:\t\t" << Job::getDiscardedJobs() << endl;
	cout << "Total hops (finished):\t" << Job::getFinishedJobTotalHops() << endl;
	long totalhops = Job::getFinishedJobTotalHops() + (c.nodes-1) * Job::getDiscardedJobs();
	cout << "Total hops (all):\t" << totalhops << endl;
	cout << "Hops/job (finished):\t" << (double)Job::getFinishedJobTotalHops()/Job::getFinishedJobs() << endl;
	cout << "Hops/job (total):\t" << (double)totalhops/Job::getTotalJobs() << endl;
	cout << "Success ratio:\t\t" << (100.0 * Job::getFinishedJobs()) / Job::getTotalJobs() << "%" << endl;

	return 0;
}
