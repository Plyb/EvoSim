#include "../Headers/Timeline.h"

#include "../../Renderer/Headers/Time.h" // TODO: bad dependency

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
	lock.lock();
	for (int i = 0; i < 1024; i++) {
		if ((i / 10) % 2) {
			states.push_back(worldState);
		}
		else {
			states.push_back(worldState2);
		}
	}
	lock.unlock();
}

bool Timeline::tryGetStateAtFrame(int frame, WorldState& worldState) {
	if (!lock.try_lock()) {
		return false;
	}
	if (frame >= states.size()) {
		lock.unlock();
		return false;
	}
	worldState = states.at(frame);
	lock.unlock();
	return true;
}

void Timeline::push(WorldState worldState) {
	lock.lock();
	states.push_back(worldState);
	lock.unlock();
}