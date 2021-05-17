#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Shared/Headers/Timeline.h"

class Simulator {
public:
	Simulator(Timeline& timeline);
	
	void run();
private:
	Timeline* timeline;
};

#endif // !SIMULATOR_H

