#include "../Headers/Timeline.h"

#include "../../Renderer/Headers/Time.h" // TODO: bad dependency

WorldState states[1024];

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

Timeline::Timeline() {
	Time::start();
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
			states[i] = worldState;
		}
		else {
			states[i] = worldState2;
		}
	}
}

bool Timeline::tryGetStateAtFrame(int frame, WorldState& worldState) {
	if (frame >= 1024) {
		return false;
	}
	worldState = states[frame];
	return true;
}

void Timeline::push(WorldState worldState) {
	// TODO: this isn't actually implemented at the moment
}