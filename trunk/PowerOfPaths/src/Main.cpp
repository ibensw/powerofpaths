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

void preload(Configuration c, Ring* r){
	double rnd;
	double l;
	double load = c.length/c.arrival;
	for (unsigned int i = 0; i < r->getSize(); ++i){
		rnd = (double)rand() / (double)RAND_MAX;
		if (rand() < load){
			l=exp_distr(c.joblength);
			r->getSimulator()->addEvent(new ArriveEvent(0.0, new Job(c.makeInfoFunction(l)), r->getNode(i)));			
		}
	}
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

	double success = 0.0;
	double avghops = 0.0;

	cout.setf(ios::fixed,ios::floatfield);
	cout.precision(12);

#pragma omp parallel for
	for (unsigned int i = 0; i < c.repeat; ++i){
		Ring r(c.nodes, c.nodeSize, c.makeNodeFunction);

		//preload(c, &r); //disabled to compare output to more early results

		fillEvents(c, &r);

		if (c.progressinterval <= 0){
			r.getSimulator()->run();
		}else{
			r.getSimulator()->run(c.progressinterval);
		}

#pragma omp critical
		{
			cout << "--------------------------" << endl;
			cout << "Run: " << i << endl;
			cout << "Total jobs:\t\t" << r.getTotalJobs() << endl;
			cout << "Finished jobs:\t\t" << r.getFinishedJobs() << endl;
			cout << "Discarded jobs:\t\t" << r.getDiscardedJobs() << endl;
			cout << "Total hops (finished):\t" << r.getFinishedJobTotalHops() << endl;
			long totalhops = r.getFinishedJobTotalHops() + (c.nodes-1) * r.getDiscardedJobs();
			cout << "Total hops (all):\t" << totalhops << endl;
			cout << "Hops/job (finished):\t" << (double)r.getFinishedJobTotalHops()/r.getFinishedJobs() << endl;
			cout << "Hops/job (total):\t" << (double)totalhops/r.getTotalJobs() << endl;
			cout << "Success ratio:\t\t" << (100.0 * r.getFinishedJobs()) / r.getTotalJobs() << "%" << endl;
			success+=(double)(r.getFinishedJobs()) / r.getTotalJobs();
			avghops+=(double)r.getFinishedJobTotalHops()/r.getFinishedJobs();
		}
	}

	if (c.repeat > 1){
		cout << "--------------------------" << endl;
		cout << "Avg. hops/job (finished):\t" << avghops / c.repeat << endl;
		cout << "Avg. success ratio:\t\t" << 100.0 * success / c.repeat << "%" << endl;
	}

	return 0;
}
