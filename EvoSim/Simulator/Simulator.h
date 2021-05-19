#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "../Shared/Headers/Timeline.h"

class Simulator {
public:
	Simulator(Timeline& timeline);
	
	void run();
private:
	Timeline* timeline;

	WorldState latestState;

	void updateCreatures();
	void remap();
	void updateGround();
	void updateCreatureList();
};

#endif // !SIMULATOR_H

