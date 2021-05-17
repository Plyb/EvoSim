#include "../Headers/Timeline.h"

Timeline::Timeline() {}

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