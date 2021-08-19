#include "../Headers/Timeline.h"

#include <iostream>
#include <chrono>
#include <thread>
#include "../Headers/TimelineSerializer.h"

Timeline::Timeline() {
	pushEpoch = new Epoch();
	TimelineSerializer::initializeDirectory();
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

Timeline::Batch::Batch(Timeline* timeline) : timeline(timeline) {
	if (!timeline->lock.try_lock()) {
		throw AlreadyLockedException();
	}
}

Timeline::Batch::~Batch() {
	timeline->lock.unlock();
}

bool Timeline::Batch::getStateAtFrame(int frame, WorldState*& worldState) {
	if (frame >= timeline->epochs.size() * Epoch::MAX_SIZE) {
		return false;
	}
	worldState = timeline->epochs.at(frame / Epoch::MAX_SIZE)->getAt(frame % Epoch::MAX_SIZE);
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