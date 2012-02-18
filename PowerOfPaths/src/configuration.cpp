#include <iostream>
#include <stdlib.h>
#include "configuration.h"
#include "nodes.h"

using namespace std;

void help(){
	cout << "Usage: -r -s long -j double -a double -n long -p long -l long -t long -h type" << endl;
	cout << "\t-r\tRandom seed" << endl;
	cout << "\t-s\tSet seed\t\t\t(default: 0)" << endl;
	cout << "\t-j\tJob length\t\t\t(default: 1.0)" << endl;
	cout << "\t-a\tInterarrival time\t\t(default: 1.0)" << endl;
	cout << "\t-n\tRing size\t\t\t(default: 100)" << endl;
	cout << "\t-c\tProcessing units per node\t(default: 1)" << endl;
	cout << "\t-p\tPrint progress interval\t(default: -1 - disabled)" << endl;
	cout << "\t-l\tSimulation length\t\t(default: 3600)" << endl;
	cout << "\t-t\tRepetition\t\t(default: 1)" << endl;
	cout << "\t-h\tPrint this help" << endl;
	cout << "\t type\tright | switch | randswitch | evenswitch | prime | randprime | randunvisited | totop" << endl;
}

template <typename T>
pop::JobInfo* createJI(double len){
	return new T(len);
}

template <typename T>
pop::Node* createN(unsigned int id, pop::Ring* ring, unsigned int size){
	return new T(id, ring, size);
}

Configuration::Configuration(int argc, char** argv):
	seed(0), joblength(1.0),
	arrival(1.0), nodes(100), nodeSize(1), progressinterval(-1), length(3600),
	repeat(1), makeNodeFunction(0), makeInfoFunction(0)
{
	int c;
	int index;
	while ((c = getopt (argc, argv, "rs:j:a:n:c:p:l:hv:t:")) != -1){
		switch (c){
		case 'r':
			seed = time(0);
			break;
		case 's':
			seed = atol(optarg);
			break;
		case 'j':
			joblength = atof(optarg);
			break;
		case 'a':
			arrival = atof(optarg);
			break;
		case 'n':
			nodes = atol(optarg);
			break;
		case 'c':
			nodeSize = atol(optarg);
			break;
		case 'p':
			progressinterval = atoi(optarg);
			break;
		case 'l':
			length = atol(optarg);
			break;
		case 't':
			repeat = atol(optarg);
			break;
		case 'h':
			help();
			exit(0);
			break;
		case 'v':
			RandSwitchNode::setValue(atof(optarg));
			break;
		default:
			cout << "Unknown option: " << optopt << endl;
			break;
		}
	}

	srand(seed);
	cout << "Seed: " << seed << endl;

	for (index = optind; index < argc; index++){
		string arg = argv[index];
		if (arg == "right"){
			makeNodeFunction = createN<RightNode>;
			makeInfoFunction = createJI<RightNode::info_type>;
		}
		if (arg == "switch"){
			makeNodeFunction = createN<SwitchNode>;
			makeInfoFunction = createJI<SwitchNode::info_type>;
		}
		if (arg == "randswitch"){
			makeNodeFunction = createN<RandSwitchNode>;
			makeInfoFunction = createJI<RandSwitchNode::info_type>;
		}
		if (arg == "evenswitch"){
			makeNodeFunction = createN<EvenSwitchNode>;
			makeInfoFunction = createJI<EvenSwitchNode::info_type>;
		}
		if (arg == "prime"){
			makeNodeFunction = createN<PrimeNode>;
			makeInfoFunction = createJI<PrimeNode::info_type>;
		}
		if (arg == "randprime"){
			makeNodeFunction = createN<RandPrimeNode>;
			makeInfoFunction = createJI<RandPrimeNode::info_type>;
		}
		if (arg == "randunvisited"){
			makeNodeFunction = createN<RandUnvisited>;
			makeInfoFunction = createJI<RandUnvisited::info_type>;
		}
		if (arg == "totop"){
			makeNodeFunction = createN<ToTopNode>;
			makeInfoFunction = createJI<ToTopNode::info_type>;
		}
		if (arg == "rrunvisited"){
			makeNodeFunction = createN<RRUnvisited>;
			makeInfoFunction = createJI<RRUnvisited::info_type>;
		}
	}

	if (!makeNodeFunction){
		cerr << "No type given" << endl;
		exit(1);
	}
}

