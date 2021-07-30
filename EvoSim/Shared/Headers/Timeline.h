#ifndef TIMELINE_H
#define TIMELINE_H

#include "WorldState.h"
#include "MethodCallback.h"
#include <mutex>
#include <vector>
#include <exception>

class Timeline {
public:
	Timeline();
	void push(WorldState* worldState);
	bool getIsFull();
	unsigned int getNumFramesAvailable() const;

	class Batch {
	public:
		Batch(Timeline* timeline);
		~Batch();
		bool getStateAtFrame(int frame, WorldState*& worldState);

		class AlreadyLockedException : public std::exception {};
	private:
		Timeline* timeline;
	} friend;
private:
	static const int MAX_EPOCHS = 160;
	bool isFull = false;

	class Epoch {
	public:
		static const int MAX_SIZE = 128;

		void push(WorldState* worldstate);
		int getSize();
		WorldState* getAt(int index);
	private:

		int size = 0;
		WorldState* states[MAX_SIZE];
	};
	Epoch* pushEpoch;

	std::mutex lock;
	std::vector<Epoch*> epochs;

	unsigned int numFramesAvailable = 0;
};

#endif // !TIMELINE_H

