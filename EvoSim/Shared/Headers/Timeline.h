#ifndef TIMELINE_H
#define TIMELINE_H

#include "WorldState.h"

class Timeline {
public:
	Timeline();
	bool tryGetStateAtFrame(int frame, WorldState& worldState);
	void push(WorldState worldState);
};

#endif // !TIMELINE_H

