#ifndef TIMELINE_H
#define TIMELINE_H

#include "../../Shared/Headers/WorldState.h"

class Timeline {
public:
	Timeline();
	bool tryGetStateAtFrame(int frame, WorldState& worldState);
};

#endif // !TIMELINE_H

