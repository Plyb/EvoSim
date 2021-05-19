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
	WorldState worldState = {
		{
			creatureStates
		},
		{
			1
		}
	};
	while (true) {
		worldState.creatures[0].rot += 0.1f;
		timeline->push(worldState);
	}
}