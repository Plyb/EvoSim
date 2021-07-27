#include "Simulator.h"

#include <iostream>


Simulator::Simulator(Timeline& timeline) : timeline(&timeline) {
	//set up initial state
	CreatureState* creatureState = new CreatureState {
		++CreatureState::LAST_ID, 0.0f, 0.0f, 0.0f
	};
	Creature* creature = new Creature(creatureState);
	creatures.push_back(creature);
};

void Simulator::run() {
	while (!timeline->getIsFull()) {
		updateCreatures();
		remap();
		updateGround();
		updateCreatureList();
		timeline->push(createState());
	}
}

// TODO: this can be parallelized
void Simulator::updateCreatures() {
	for (Creature* creature : creatures) {
		creature->update(ground);
	}
}

void Simulator::remap() {
	for (unsigned int x = 0; x < WorldState::WORLD_WIDTH; x++) {
		for (unsigned int y = 0; y < WorldState::WORLD_WIDTH; y++) {
			ground[x][y].clearVisitingCreatures();
		}
	}

	for (Creature* creature : creatures) {
		creature->remapCell(ground);
	}
}

// TODO: this can be parallelized
void Simulator::updateGround() {
	for (unsigned int x = 0; x < WorldState::WORLD_WIDTH; x++) {
		for (unsigned int y = 0; y < WorldState::WORLD_WIDTH; y++) {
			ground[x][y].update();
		}
	}
}

void Simulator::updateCreatureList() {
	removeCreatures();
	addCreatures();
}

void Simulator::removeCreatures() {
	for (int i = creatures.size() - 1; i >= 0; i--) {
		if (creatures.at(i)->getState()->energy < 0) {
			delete creatures.at(i);
			creatures.erase(creatures.begin() + i);
		}
	}
}

void Simulator::addCreatures() {
	std::vector<Creature*> creaturesToAdd;
	for (Creature* creature : creatures) {
		if (creature->isReproducing(ground)) {
			creaturesToAdd.push_back(creature->reproduce());
		}
	}

	for (Creature* creature : creaturesToAdd) {
		creatures.push_back(creature);
	}
}

WorldState* Simulator::createState() const {
	WorldState* state = new WorldState();

	std::map<long long, CreatureState>* creatureStates = new std::map<long long, CreatureState>();
	for (Creature* creature : creatures) {
		creatureStates->insert(std::pair<long long, CreatureState>(creature->getState()->id, *creature->getState()));
	}
	state->creatures = *creatureStates;

	for (unsigned int x = 0; x < WorldState::WORLD_WIDTH; x++) {
		for (unsigned int y = 0; y < WorldState::WORLD_WIDTH; y++) {
			state->ground[x][y] = *ground[x][y].getState();
		}
	}

	return state;
}