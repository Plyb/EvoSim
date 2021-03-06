#include "Simulator.h"

#include <iostream>
#include <math.h>
#include <omp.h>


Simulator::Simulator(Timeline& timeline) : timeline(&timeline) {
	//set up initial state
	CreatureState* creatureState = new CreatureState {
		++CreatureState::LAST_ID, 50.0f, 50.0f, 0.0f
	};

	std::vector<Eigen::MatrixXd> defaultWeights{ (Eigen::MatrixXd(7, 8) <<
		0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0).finished()
	};

	creatureState->mind = new CreatureMind(defaultWeights);
	Creature* creature = new Creature(creatureState);

	creatures.push_back(creature);
};

void Simulator::run() {
	while (!timeline->getIsFull()) {
		remap();
		updateCreatures();
		updateGround();
		updateCreatureList();
		timeline->push(createState());
	}
}

// TODO: this can be parallelized
void Simulator::updateCreatures() {
	omp_set_num_threads((creatures.size() / UPDATE_CREATURES_CHUNK_SIZE) + 1);
#pragma omp parallel for
	for (int i = 0; i < creatures.size(); i++) {
		Creature* creature = creatures.at(i);
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
		if (creatures.at(i)->isDying()) {
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

	if (creatures.size() == 0) {
		for (unsigned int i = 0; i < 15; i++) {
			CreatureState* creatureState = new CreatureState{
				++CreatureState::LAST_ID, (float)(rand() % 100), (float)(rand() % 100), (float)rand()
			};
			creatureState->mind = new CreatureMind(creatureState->id);
			Creature* creature = new Creature(creatureState);
			creatures.push_back(creature);
		}
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