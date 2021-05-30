#include "Simulator.h"

#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>

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
		timeline->push(new WorldState(latestState));
	}
}

// TODO: this can be parallelized
void Simulator::updateCreatures() {
	latestState->creatures[0].rot += 0.1f;
	latestState->creatures[0].xpos += cos(latestState->creatures[0].rot * M_PI / 180) / 100.0f;
	latestState->creatures[0].ypos += sin(latestState->creatures[0].rot * M_PI / 180) / 100.0f;
}

void Simulator::remap() {
	for (unsigned int x = 0; x < WorldState::WORLD_WIDTH; x++) {
		for (unsigned int y = 0; y < WorldState::WORLD_WIDTH; y++) {
			latestState->ground[x][y].numCreatures = 0;
		}
	}

	for (CreatureState creature : latestState->creatures) {
		int xpos = (int)creature.xpos;
		int ypos = (int)creature.ypos;
		if (xpos < 0 || xpos >= WorldState::WORLD_WIDTH || ypos < 0 || ypos >= WorldState::WORLD_WIDTH) {
			continue;
		}

		CellState& cell = latestState->ground[xpos][ypos];
		cell.creatures[cell.numCreatures] = &creature;
		cell.numCreatures++;
	}
}

// TODO: this can be parallelized
void Simulator::updateGround() {
	for (unsigned int i = 0; i < NUM_CELLS_TO_UPDATE; i++) {
		unsigned int x = rand() % WorldState::WORLD_WIDTH;
		unsigned int y = rand() % WorldState::WORLD_WIDTH;
		latestState->ground[x][y].food += FOOD_BOOST;
	}

	for (unsigned int x = 0; x < WorldState::WORLD_WIDTH; x++) {
		for (unsigned int y = 0; y < WorldState::WORLD_WIDTH; y++) {
			unsigned char& oldFood = latestState->ground[x][y].food;
			unsigned char newFood = oldFood - latestState->ground[x][y].numCreatures;
			if (newFood < oldFood) {
				oldFood = newFood;
			}
		}
	}
}

void Simulator::updateCreatureList() {

}