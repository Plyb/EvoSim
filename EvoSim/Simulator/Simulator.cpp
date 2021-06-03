#include "Simulator.h"

#include <iostream>


Simulator::Simulator(Timeline& timeline) : timeline(&timeline) {
	//set up initial state
	CreatureState creatureState = {
		0.0f, 0.0f, 0.0f
	};
	std::vector<CreatureState> creatureStates = {
		creatureState,
	};
	currentState = new WorldState(creatureStates);

	creatures.push_back(new Creature(&currentState->creatures[0]));
};

void Simulator::run() {
	while (!timeline->getIsFull()) {
		updateCreatures();
		remap();
		updateGround();
		updateCreatureList();
		timeline->push(new WorldState(currentState));
	}
}

// TODO: this can be parallelized
void Simulator::updateCreatures() {
	for (Creature* creature : creatures) {
		creature->update();
	}
}

void Simulator::remap() {
	for (unsigned int x = 0; x < WorldState::WORLD_WIDTH; x++) {
		for (unsigned int y = 0; y < WorldState::WORLD_WIDTH; y++) {
			currentState->ground[x][y].numCreatures = 0;
		}
	}

	for (CreatureState creature : currentState->creatures) {
		CellState* cell = currentState->cellAt(creature);
		if (cell == NULL) {
			continue;
		}

		cell->creatures[cell->numCreatures] = &creature;
		cell->numCreatures++;
	}
}

// TODO: this can be parallelized
void Simulator::updateGround() {
	for (unsigned int i = 0; i < NUM_CELLS_TO_UPDATE; i++) {
		unsigned int x = rand() % WorldState::WORLD_WIDTH;
		unsigned int y = rand() % WorldState::WORLD_WIDTH;
		currentState->ground[x][y].food += FOOD_BOOST;
	}

	for (unsigned int x = 0; x < WorldState::WORLD_WIDTH; x++) {
		for (unsigned int y = 0; y < WorldState::WORLD_WIDTH; y++) {
			unsigned char& oldFood = currentState->ground[x][y].food;
			unsigned char newFood = oldFood - currentState->ground[x][y].numCreatures;
			if (newFood < oldFood) {
				oldFood = newFood;
			}
		}
	}
}

void Simulator::updateCreatureList() {

}