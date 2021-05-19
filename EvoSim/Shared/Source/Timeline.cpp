#include "../Headers/Timeline.h"

#include <iostream>

Timeline::Timeline() {
	pushEpoch = new Epoch();
}

bool Timeline::tryGetStateAtFrame(int frame, WorldState& worldState) {
	if (!lock.try_lock()) {
		return false;
	}
	if (frame >= epochs.size() * Epoch::MAX_SIZE) {
		lock.unlock();
		return false;
	}
	worldState = epochs.at(frame / Epoch::MAX_SIZE)->getAt(frame % Epoch::MAX_SIZE);
	lock.unlock();
	return true;
}

void Timeline::push(WorldState worldState) {
	pushEpoch->push(worldState);
	if (pushEpoch->getSize() == Epoch::MAX_SIZE) {
		lock.lock();
		epochs.push_back(pushEpoch);
		lock.unlock();
		pushEpoch = new Epoch();
	}
}

void Timeline::Epoch::push(WorldState worldState) {
	if (this->size == this->MAX_SIZE) {
		throw std::out_of_range("Pushed to many items to Epoch without clearing");
	}
	this->states[this->size] = worldState;
	this->size++;
}

int Timeline::Epoch::getSize() {
	return this->size;
}

WorldState Timeline::Epoch::getAt(int index) {
	if (index >= this->size) {
		throw std::out_of_range("Tried accessing nonexistent element of epoch");
	}
	return this->states[index];
}