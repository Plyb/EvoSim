#ifndef TIMELINE_H
#define TIMELINE_H

#include "WorldState.h"
#include <mutex>
#include <vector>

class Timeline {
public:
	Timeline();
	bool tryGetStateAtFrame(int frame, WorldState& worldState);
	void push(WorldState worldState);
private:

	class Epoch {
	public:
		static const int MAX_SIZE = 1024;

		void push(WorldState worldstate);
		int getSize();
		WorldState getAt(int index);
	private:
		int size = 0;
		WorldState states[MAX_SIZE];
	};
	Epoch* pushEpoch;

	std::mutex lock;
	std::vector<Epoch*> epochs;
};

#endif // !TIMELINE_H

