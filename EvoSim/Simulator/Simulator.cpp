#include "Simulator.h"

#include <iostream>

Simulator::Simulator(Timeline& timeline) : timeline(&timeline) {};

// TODO: this is temporary for testing
CreatureState creature1 = {
	0.0f, 0.0f, 0.0f
};

std::vector<CreatureState> creatureStates = {
	creature1,
};

void Simulator::run() {
	latestState = {
		{
			creatureStates
		},
		{
			1
		}
	};

	while (true) {
		updateCreatures();
		remap();
		updateGround();
		updateCreatureList();
		timeline->push(latestState);
	}
}

// TODO: this can be parallelized
void Simulator::updateCreatures() {
	latestState.creatures[0].rot += 0.1f;
}

void Simulator::remap() {

}

// TODO: this can be parallelized
void Simulator::updateGround() {

}

void Simulator::updateCreatureList() {

}