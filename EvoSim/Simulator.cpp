#include "Simulator.h"

#include <iostream>

Simulator::Simulator(Timeline& timeline) : timeline(&timeline) {};

// TODO: this is temporary for testing
CreatureState creature1 = {
	0.0f, 0.0f, 0.0f
};

CreatureState creature2 = {
200.0f, 100.0f, 0.0f
};

CreatureState creature3 = {
100.0f, 300.0f, 0.0f
};

CreatureState creatureStates[] = {
	creature1,
	creature2,
	creature3
};

CreatureState creatureStates2[] = {
	creature1,
	creature2
};

void Simulator::run() {
	WorldState worldState;
	WorldState worldState2 = {
		{
			creatureStates
		},
		{
			3
		}
	};
	worldState = {
		{
			creatureStates2
		},
		{
			2
		}
	};
	for (int i = 0; i < 1024; i++) {
		if ((i / 10) % 2) {
			timeline->push(worldState);
		}
		else {
			timeline->push(worldState2);
		}
	}
	std::cout << "Done pushing initial states" << std::endl;

	// TODO spinning for now for testing
	while (true) {}
}