/*
 * configuration.h
 *
 *  Created on: Oct 6, 2011
 *      Author: ibensw
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "ring/node.h"
#include "ring/job.h"

void help();

typedef pop::Node* (*makeNodeType)(unsigned int i, pop::Ring* r);
typedef pop::JobInfo* (*makeInfoType)(double length);
struct Configuration{
	long seed;
	double joblength;
	double arrival;
	long nodes;
	long progressinterval;
	long length;
	makeNodeType makeNodeFunction;
	makeInfoType makeInfoFunction;
	
	Configuration(int argc, char** argv);
};

#endif /* CONFIGURATION_H_ */
