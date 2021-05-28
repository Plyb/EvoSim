#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "../Shared/Headers/Timeline.h"

class Simulator {
public:
	Simulator(Timeline& timeline);
	
	void run();
private:
	Timeline* timeline;

	WorldState* latestState;

	void updateCreatures();
	void remap();
	void updateGround();
	void updateCreatureList();

	static const unsigned int NUM_CELLS_TO_UPDATE = 10;
	static const unsigned int FOOD_BOOST = 16;
};

#endif // !SIMULATOR_H

