/*
 * simulator.cpp
 *
 *  Created on: Sep 26, 2011
 *      Author: ibensw
 */

#include "simulator.h"
#include <iostream>
using namespace std;

namespace pop {

Simulator::Simulator():
	fNow(0.0)
		{}

Simulator::~Simulator() {
}

void Simulator::run(){
	while(!fPending.empty()){
		Schedule x = fPending.top();
		fPending.pop();
		fNow = x.getEvent()->getScheduleTime();
		x.getEvent()->run(this);
	}
}

void Simulator::run(int interval){
	int next = interval;
	while(!fPending.empty()){
		Schedule x = fPending.top();
		fPending.pop();
		fNow = x.getEvent()->getScheduleTime();
		if (fNow > next){
			cout << "Time: " << fNow << "\tPending events: " << fPending.size() << endl;
			next+=interval;
		}
		x.getEvent()->run(this);
	}
}

void Simulator::addEvent(Event* e){
	fPending.push(Schedule(e));
}

}
