#include "Simulator.h"

#include <iostream>

// TODO: this is temporary for testing
CreatureState creature1 = {
	0.0f, 0.0f, 0.0f
};

std::vector<CreatureState> creatureStates = {
	creature1,
};

Simulator::Simulator(Timeline& timeline) : timeline(&timeline), latestState(new WorldState(creatureStates)) {};

void Simulator::run() {
	while (true) {
		updateCreatures();
		remap();
		updateGround();
		updateCreatureList();
		timeline->push(*latestState);
	}
}

// TODO: this can be parallelized
void Simulator::updateCreatures() {
	latestState->creatures[0].rot += 0.1f;
}

void Simulator::remap() {

}

// TODO: this can be parallelized
void Simulator::updateGround() {
	for (unsigned int i = 0; i < NUM_CELLS_TO_UPDATE; i++) {
		unsigned int x = rand() % WorldState::WORLD_WIDTH;
		unsigned int y = rand() % WorldState::WORLD_WIDTH;
		latestState->ground[x][y].food += FOOD_BOOST;
	}
}

void Simulator::updateCreatureList() {

}