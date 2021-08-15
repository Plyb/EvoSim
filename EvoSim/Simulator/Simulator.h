#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "../Shared/Headers/Timeline.h"
#include "Creature.h"
#include "Cell.h"

class Simulator {
public:
	Simulator(Timeline& timeline);
	
	void run();
private:
	Timeline* timeline;

	// State
	std::vector<Creature*> creatures; // TODO make this a list, not a vector
	Cell ground[WorldState::WORLD_WIDTH][WorldState::WORLD_WIDTH];

	void updateCreatures();
	void remap();
	void updateGround();
	void updateCreatureList();

	void removeCreatures();
	void addCreatures();

	WorldState* createState() const; // TODO make this const

	static const unsigned int UPDATE_CREATURES_CHUNK_SIZE = 4000; // How many creatures to update in a multithreading chunk.
};

#endif // !SIMULATOR_H

