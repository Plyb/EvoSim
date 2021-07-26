#include "../Headers/Timeline.h"

#include <iostream>
#include <chrono>
#include <thread>

Timeline::Timeline() {
	pushEpoch = new Epoch();
}

bool Timeline::tryGetStateAtFrame(int frame, WorldState*& worldState) {
	if (!lock.try_lock()) {
		return false;
	}
	bool success = getStateAtFrameUnguarded(frame, worldState);
	lock.unlock();
	return success;
}

bool Timeline::getStateAtFrameUnguarded(int frame, WorldState*& worldState) {
	if (frame >= epochs.size() * Epoch::MAX_SIZE) {
		return false;
	}
	worldState = epochs.at(frame / Epoch::MAX_SIZE)->getAt(frame % Epoch::MAX_SIZE);
}

bool Timeline::tryCallbackGuarded(MethodCallback<void, bool> callback) {
	if (!lock.try_lock()) {
		return false;
	}
	bool success = callback();
	lock.unlock();
	return success;
}

void Timeline::push(WorldState* worldState) {
	pushEpoch->push(worldState);
	if (pushEpoch->getSize() == Epoch::MAX_SIZE) {
		lock.lock();
		epochs.push_back(pushEpoch);
		numFramesAvailable += Epoch::MAX_SIZE;
		lock.unlock();
		pushEpoch = new Epoch();
		if (epochs.size() == MAX_EPOCHS) {
			isFull = true;
		}
	}
}

bool Timeline::getIsFull() {
	return isFull;
}

unsigned int Timeline::getNumFramesAvailable() const {
	return numFramesAvailable;
}

void Timeline::Epoch::push(WorldState* worldState) {
	if (this->size == this->MAX_SIZE) {
		throw std::out_of_range("Pushed too many items to Epoch without clearing");
	}
	this->states[this->size] = worldState;
	this->size++;
}

int Timeline::Epoch::getSize() {
	return this->size;
}

WorldState* Timeline::Epoch::getAt(int index) {
	if (index >= this->size) {
		throw std::out_of_range("Tried accessing nonexistent element of epoch");
	}
	return this->states[index];
}