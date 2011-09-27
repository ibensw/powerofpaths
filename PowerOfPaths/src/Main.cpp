#include <iostream>
#include "simulator/event.h"
#include "simulator/simulator.h"

using namespace std;
using namespace pop;

class TestEvent: public Event{
public:
	TestEvent(double when, int a);

	void run(Simulator* s);

private:
	int fA;
};

TestEvent::TestEvent(double when, int a):
	Event(when)
	{
	fA = a;
}

void TestEvent::run(Simulator* s){
	cout << "Running event " << fA << " at " << s->getTime() << endl;
}

int main() {
	Simulator sim;
	sim.addEvent(new TestEvent(1.0, 1));
	sim.addEvent(new TestEvent(3.0, 3));
	sim.addEvent(new TestEvent(2.0, 2));
	sim.addEvent(new TestEvent(0.0, 0));
	sim.run();
	return 0;
}
