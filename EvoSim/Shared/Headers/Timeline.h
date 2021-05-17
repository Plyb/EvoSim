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
	std::mutex lock;
	std::vector<WorldState> states;
};

#endif // !TIMELINE_H

